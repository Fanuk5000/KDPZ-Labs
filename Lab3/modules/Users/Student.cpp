#include "Student.h"

Student::Student(QString id, QString name, QString surname,
                 QString password, QString groupID)
    : User(std::move(id), std::move(name), std::move(surname), std::move(password)),
      groupID(std::move(groupID))
{
}

int Student::getScore() const
{
    return score;
}

void Student::setScore(const int new_score) { this->score = new_score; }

void Student::addScore(const int new_score) { this->score += new_score; }

QString Student::getGroupID() const { return groupID; }
