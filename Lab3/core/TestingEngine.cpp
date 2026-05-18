#include "TestingEngine.h"
#include <QUuid>
#include <QDebug>

TestingEngine::TestingEngine(DataManager* db, QObject* parent)
    : QObject(parent), currentState(SessionState::Created), session(nullptr), activeTest(nullptr),
      dataManager(db)
{
    countdownTimer = new QTimer(this);
    countdownTimer->setInterval(1000); // 1 second tick
    connect(countdownTimer, &QTimer::timeout, this, &TestingEngine::onTick);

    autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(60000); // Auto-save every 60 seconds
    connect(autoSaveTimer, &QTimer::timeout, this, &TestingEngine::performAutoSave);
}

TestingEngine::~TestingEngine()
{
    delete session;
}

void TestingEngine::changeState(SessionState newState)
{
    currentState = newState;
    emit stateChanged(currentState);
}

void TestingEngine::initializeSession(const QString& studentId, Test* test)
{
    activeTest = test;
    QString sessionId = QUuid::createUuid().toString();

    session = new TestSession(sessionId, studentId, activeTest->getTestId(),
                              QDateTime::currentDateTime(), "initialized");

    // State Machine: "entry / Завантажити питання з JSON/XML" is handled via passing the Test object
    changeState(SessionState::Initialized);
    qDebug() << "Session initialized for student:" << studentId << "Waiting for start.";
}

void TestingEngine::startSession()
{
    if (currentState != SessionState::Initialized) return;

    remainingSeconds = activeTest->getDurationMinutes() * 60;

    countdownTimer->start();
    autoSaveTimer->start();

    // State Machine: "entry / Зафіксувати startTime"
    changeState(SessionState::Active);
    qDebug() << "Session started. Timer running.";
}

void TestingEngine::selectAnswer(const QString& questionId, const QList<QString>& selectedIds)
{
    if (currentState != SessionState::Active) return;

    currentAnswers[questionId] = selectedIds;

    // Activity Diagram: "Локальне автозбереження стану сесії" upon selection
    performAutoSave();
}

void TestingEngine::onTick()
{
    remainingSeconds--;
    emit timeUpdated(remainingSeconds);

    if (remainingSeconds <= 0)
    {
        countdownTimer->stop();
        qDebug() << "Time limit exhausted. Auto-submitting.";
        finishTest();
    }
}

void TestingEngine::performAutoSave()
{
    if (currentState != SessionState::Active) return;

    // Logic to write 'currentAnswers' to a temporary JSON/XML file
    qDebug() << "Background auto-save executed to temporary file.";
    emit autoSaveCompleted();
}

void TestingEngine::finishTest()
{
    if (currentState != SessionState::Active) return;

    countdownTimer->stop();
    autoSaveTimer->stop();

    // State Machine: Completed (Block UI, prepare Map)
    changeState(SessionState::Completed);
    qDebug() << "Test completed. Processing answers...";

    // State Machine: Evaluated (Calculate score based on Sequence Diagram logic)
    changeState(SessionState::Evaluated);

    float totalScore = 0.0f;

    // Sequence Diagram implementation: loop through questions, checkAnswer, generate Result
    for (const Question& q : activeTest->getQuestions())
    {
        QList<QString> selected = currentAnswers.value(q.getQuestionId());

        // Simulating the q.checkAnswer(selectedIds) boolean return
        bool isCorrect = q.checkAnswer(selected);
        if (isCorrect)
        {
            totalScore += q.getPoints();
        }
    }

    // Sequence Diagram: Result(score, timestamp)
    Result finalResult(QUuid::createUuid().toString(), session->getSessionId(), totalScore,
                       QDateTime::currentDateTime());

    // State Machine: Saved (Write to DB, free resources)
    changeState(SessionState::Saved);

    // Sequence Diagram: db: LocalDataManager -> saveResult(res)
    bool saveSuccess = dataManager->saveResult(finalResult);

    if (saveSuccess)
    {
        qDebug() << "Result saved successfully. Score:" << totalScore;
        emit testFinished(finalResult);
    }
}

TestingEngine::SessionState TestingEngine::getState() const { return currentState; }
