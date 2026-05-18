#include "TestSession.h"

TestSession::TestSession(QString sId, QString stId, QString tId, QDateTime start, QString stat)
    : sessionId(std::move(sId)), studentId(std::move(stId)), testId(std::move(tId)),
      startTime(std::move(start)), status(std::move(stat))
{
}

bool TestSession::canStart() const
{
    return status != "completed" && status != "in_progress";
}

void TestSession::autoSubmit()
{
    status = "completed";
    qDebug() << "Сесію" << sessionId << "було автоматично завершено.";
}

void TestSession::submitAnswers(const QMap<QString, QString>& answers)
{
    if (status == "in_progress")
    {
        status = "completed";
        qDebug() << "Відповіді успішно збережено для сесії" << sessionId <<
            ". Кількість відповідей:" << answers.size();
    }
}

QString TestSession::getSessionId() const { return sessionId; }
QString TestSession::getStatus() const { return status; }
