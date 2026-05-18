#pragma once

#include "QString"
#include "QDateTime"

class Result
{
    private:
        QString resultId;
        QString sessionId;
        float score;
        QDateTime timestamp;

    public:
        Result(QString resultId, QString sessionId, float score, QDateTime timestamp);
        QString generateReport() const;
        QString getResultId() const;
        QString getSessionId() const;
        float getScore() const;
        QDateTime getTimestamp() const;
};
