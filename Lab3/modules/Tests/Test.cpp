#include "Test.h"

Test::Test(QString id, QString title, int duration, int attempts, QList<QString> groups,
           QList<Question> testQuestions)
    : testId(std::move(id)), title(std::move(title)), durationMinutes(duration),
      maxAttempts(attempts), assignedGroupIds(std::move(groups)),
      questions(std::move(testQuestions))
{
}

float Test::calculateMaxScore() const
{
    float totalScore = 0.0f;
    for (const Question& q : questions)
    {
        totalScore += q.getPoints();
    }
    return totalScore;
}

bool Test::isAvailableForGroup(const QString& groupId) const
{
    return assignedGroupIds.contains(groupId);
}

void Test::addQuestion(Question q) { questions.append(std::move(q)); }

QString Test::getTestId() const { return testId; }
QString Test::getTitle() const { return title; }
int Test::getDurationMinutes() const { return durationMinutes; }
int Test::getMaxAttempts() const { return maxAttempts; }
const QList<Question>& Test::getQuestions() const { return questions; }
const QList<QString>& Test::getAssignedGroupIds() const { return assignedGroupIds; }
