#pragma once


#include <QTimer>
#include <QList>
#include <QString>
#include "../modules/Tests/TestSession.h"
#include "../managers/DataManager.h"

class TestingEngine : public QObject
{
        Q_OBJECT

    public:
        // Matches the states defined in the State Machine Diagram
        enum class SessionState
        {
            Created,
            Initialized,
            Active,
            Completed,
            Evaluated,
            Saved
        };

        Q_ENUM(SessionState)

    private:
        SessionState currentState;
        TestSession* session;
        Test* activeTest;
        DataManager* dataManager;

        QTimer* countdownTimer;
        QTimer* autoSaveTimer;
        int remainingSeconds;

        // Simulates the Map from the Sequence Diagram (Question ID -> List of Selected Option IDs)
        QMap<QString, QList<QString>> currentAnswers;

        void changeState(SessionState newState);

    public:
        TestingEngine(DataManager* db, QObject* parent = nullptr);
        ~TestingEngine() override;

        // Transitions to Initialized state
        void initializeSession(const QString& studentId, Test* test);

        // Transitions to Active state and starts timers
        void startSession();

        // Records an answer and triggers the auto-save condition from the Activity Diagram
        void selectAnswer(const QString& questionId, const QList<QString>& selectedIds);

        [[nodiscard]] SessionState getState() const;

    public slots:
        // Triggered by manual submit or timer exhaustion
        void finishTest();

    private slots:
        void onTick();
        void performAutoSave();

    signals:
        void stateChanged(TestingEngine::SessionState newState);
        void timeUpdated(int secondsLeft);
        void testFinished(const Result& result);
        void autoSaveCompleted();
};
