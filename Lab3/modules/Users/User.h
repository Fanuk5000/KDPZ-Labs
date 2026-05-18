#pragma once

#include <QString>

class User
{
    private:
        QString id;
        QString name;
        QString login;
        QString passwordHash;

    public:
        User(QString id, QString name, QString login, QString password);
        ~User() = default;
        [[nodiscard]] bool authenticate(const QString& check_id, const QString& check_name,
                                        const QString& check_surname,
                                        const QString& check_password) const;
        [[nodiscard]] QString getId() const;
        [[nodiscard]] QString getName() const;
        [[nodiscard]] QString getPassword() const;
        [[nodiscard]] QString getLogin() const;
};
