# pragma once

#include "User.h"


class Teacher : public User
{
    private:
        QString groupID;

    public:
        Teacher(QString id, QString name, QString surname, QString password, QString groupID);
        ~Teacher() = default;

        [[nodiscard]] QString getGroupID();
};
