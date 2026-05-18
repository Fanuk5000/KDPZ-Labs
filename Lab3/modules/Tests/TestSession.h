#pragma once

#include "QDateTime"
#include "QString"

class TestSession
{
    private:
        QString sessionId;
        QString studentId;
        QString testId;
        QDateTime startTime;
        QString status;

    public:
        TestSession(QString sessionId, QString studentId, QString testId, QDateTime start,
                    QString stat);
        bool canStart() const;
        void autoSubmit();
        void submitAnswers(const QMap<QString, QString>& answers);
        QString getSessionId() const;
        QString getStatus() const;
};
