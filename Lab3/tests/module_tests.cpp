#include <gtest/gtest.h>
#include "../modules/Tests/Test.h"
#include "../modules/Tests/Question.h"
#include "../modules/Tests/AnswerOption.h"

// Module Test: Testing interaction between Test and Question
TEST(TestModule, CalculateMaxScore) {
    AnswerOption opt("a1", "Opt");
    QList<AnswerOption> options = {opt};
    QStringList correct = {"a1"};
    
    Question q1("q1", "Cat", "Q1", 5.0f, correct, options);
    Question q2("q2", "Cat", "Q2", 10.0f, correct, options);
    
    QList<Question> questions = {q1, q2};
    QList<QString> groups = {"G1"};
    
    Test test("t1", "Math Test", 30, 1, groups, questions);
    
    EXPECT_FLOAT_EQ(test.calculateMaxScore(), 15.0f);
}

TEST(TestModule, GroupAvailability) {
    QList<Question> questions;
    QList<QString> groups = {"G1", "G2"};
    
    Test test("t1", "Math Test", 30, 1, groups, questions);
    
    EXPECT_TRUE(test.isAvailableForGroup("G1"));
    EXPECT_TRUE(test.isAvailableForGroup("G2"));
    EXPECT_FALSE(test.isAvailableForGroup("G3"));
}
