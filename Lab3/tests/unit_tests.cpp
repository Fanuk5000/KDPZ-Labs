#include <gtest/gtest.h>
#include "../modules/Users/User.h"
#include "../modules/Tests/Question.h"
#include "../modules/Tests/AnswerOption.h"

// Unit Test for User class
TEST(UserTest, AuthenticationSuccess) {
    User user("1", "John Doe", "john_l", "password123");
    EXPECT_TRUE(user.authenticate("1", "John Doe", "john_l", "password123"));
}

TEST(UserTest, AuthenticationFailure) {
    User user("1", "John Doe", "john_l", "password123");
    EXPECT_FALSE(user.authenticate("1", "John Doe", "wrong_login", "password123"));
    EXPECT_FALSE(user.authenticate("1", "John Doe", "john_l", "wrong_password"));
}

// Unit Test for Question class
TEST(QuestionTest, CheckAnswerCorrect) {
    AnswerOption opt1("a1", "Option 1");
    AnswerOption opt2("a2", "Option 2");
    QList<AnswerOption> options = {opt1, opt2};
    QStringList correctIds = {"a1"};
    
    Question q("q1", "General", "What is 1+0?", 1.0f, correctIds, options);
    
    QStringList userAnswer = {"a1"};
    EXPECT_TRUE(q.checkAnswer(userAnswer));
}

TEST(QuestionTest, CheckAnswerIncorrect) {
    AnswerOption opt1("a1", "Option 1");
    AnswerOption opt2("a2", "Option 2");
    QList<AnswerOption> options = {opt1, opt2};
    QStringList correctIds = {"a1"};
    
    Question q("q1", "General", "What is 1+0?", 1.0f, correctIds, options);
    
    QStringList userAnswer = {"a2"};
    EXPECT_FALSE(q.checkAnswer(userAnswer));
    
    QStringList multipleAnswer = {"a1", "a2"};
    EXPECT_FALSE(q.checkAnswer(multipleAnswer));
}
