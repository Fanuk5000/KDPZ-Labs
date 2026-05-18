
#include "AnswerOption.h"

AnswerOption::AnswerOption(QString id, QString test, bool correct)
    : optionId(std::move(id)), text(std::move(test)), isCorrect(correct)
{
}

bool AnswerOption::getIsCorrect() const
{
    return isCorrect;
}

QString AnswerOption::getOptionId() const { return optionId; }
QString AnswerOption::getText() const { return text; }
