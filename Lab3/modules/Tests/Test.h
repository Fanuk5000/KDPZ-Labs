#pragma once

#include "QList"
#include "QString"

#include "Question.h"

class Test
{
    private:
        QString testId;
        QString title;
        int durationMinutes;
        int maxAttempts;
        QList<QString> assignedGroupIds;
        QList<Question> questions; // Added association with Question

    public:
        // Updated constructor to accept questions
        Test(QString id, QString t, int dur, int attempts, QList<QString> groups,
             QList<Question> testQuestions);

        float calculateMaxScore() const;
        bool isAvailableForGroup(const QString& groupId) const;

        QString getTestId() const;
        QString getTitle() const;
        int getDurationMinutes() const;
        int getMaxAttempts() const;
        void addQuestion(Question q); // Helper method
        const QList<Question>& getQuestions() const;
        const QList<QString>& getAssignedGroupIds() const;
};
