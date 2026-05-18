#include "Result.h"

Result::Result(QString resultId, QString sessionId, const float score, QDateTime timestamp)
    : resultId(std::move(resultId)), sessionId(std::move(sessionId)), score(score),
      timestamp(std::move(timestamp))
{
}

QString Result::generateReport() const
{
    QString report = QString("Звіт для результату: %1\nСесія: %2\nБал: %3\nЧас: %4")
                     .arg(resultId)
                     .arg(sessionId)
                     .arg(score)
                     .arg(timestamp.toString(Qt::ISODate));
    return report;
}

QString Result::getResultId() const { return resultId; }
QString Result::getSessionId() const { return sessionId; }
float Result::getScore() const { return score; }
QDateTime Result::getTimestamp() const { return timestamp; }
