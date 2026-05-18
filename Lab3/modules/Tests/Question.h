#pragma once

#include <QStringList>
#include <QString>
#include "../Tests/AnswerOption.h"

class Question
{
    private:
        QString questionID;
        QString category;
        QString text;
        float points;

        QStringList correctOptionIds;
        QList<AnswerOption> options;

    public:
        Question(QString id, QString cat, QString t, float pts, QStringList correctIds,
                 QList<AnswerOption> opts);
        ~Question() = default;

        [[nodiscard]] bool checkAnswer(const QStringList& selectedIds) const;
        [[nodiscard]] float getPoints() const;
        [[nodiscard]] QString getQuestionId() const;
        [[nodiscard]] QString getText() const;
        [[nodiscard]] QString getCategory() const;
        [[nodiscard]] QStringList getCorrectOptionIds() const;
        const QList<AnswerOption>& getOptions() const;
};
