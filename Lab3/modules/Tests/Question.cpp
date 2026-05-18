#include "Question.h"


Question::Question(QString id, QString category, QString text,
                   float points,
                   QStringList correctIds,
                   QList<AnswerOption> opts)
    : questionID(std::move(id)),
      category(std::move(category)),
      text(std::move(text)),
      points(points),
      correctOptionIds(std::move(correctIds)),
      options(std::move(opts))
{
}

bool Question::checkAnswer(const QStringList& selectedIds) const
{
    if (selectedIds.size() != correctOptionIds.size())
    {
        return false;
    }
    for (const QString& id : selectedIds)
    {
        if (!correctOptionIds.contains(id))
        {
            return false;
        }
    }
    return true;
}

float Question::getPoints() const { return points; }
QString Question::getQuestionId() const { return questionID; }
QString Question::getText() const { return text; }
QString Question::getCategory() const { return category; }
QStringList Question::getCorrectOptionIds() const { return correctOptionIds; }
const QList<AnswerOption>& Question::getOptions() const { return options; }
