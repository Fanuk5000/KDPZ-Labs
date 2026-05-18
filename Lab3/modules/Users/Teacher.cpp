#include "Teacher.h"

Teacher::Teacher(QString id, QString name, QString surname, QString password, QString groupID)
    : User(std::move(id), std::move(name), std::move(surname), std::move(password)),
      groupID(std::move(groupID))
{
}

QString Teacher::getGroupID() { return groupID; }
