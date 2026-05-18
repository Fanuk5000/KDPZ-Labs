#pragma once

#include "User.h"
#include "QString"

class Student : public User
{
    private:
        int score = 0;
        QString groupID;

    public:
        Student(QString id, QString name, QString surname, QString password, QString groupID);
        ~Student() = default;

        [[nodiscard]] int getScore() const;
        [[nodiscard]] QString getGroupID() const;
        void setScore(int new_score);
        void addScore(int new_score);
};
