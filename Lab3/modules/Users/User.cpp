#include "User.h"


User::User(QString id, QString name, QString login, QString password) :
    id(std::move(id)),
    name(std::move(name)),
    login(std::move(login)),
    passwordHash(std::move(password))
{
}

bool User::authenticate(const QString& check_id, const QString& check_name,
                        const QString& check_surname,
                        const QString& check_password) const
{
    if (check_id != this->id or check_name != this->name or check_surname != this->login or
        check_password != this->passwordHash)
    {
        return false;
    }
    return true;
}

QString User::getId() const { return id; }
QString User::getName() const { return name; }
QString User::getLogin() const { return login; }
QString User::getPassword() const { return passwordHash; }

