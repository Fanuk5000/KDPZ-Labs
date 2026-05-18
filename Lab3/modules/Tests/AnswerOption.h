#pragma once
#include "QString"

class AnswerOption
{
    private:
        QString optionId;
        QString text;
        bool isCorrect;

    public:
        AnswerOption(QString id, QString test, bool correct);
        bool getIsCorrect() const;
        QString getOptionId() const;
        QString getText() const;
};
