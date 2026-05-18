#pragma once

#include "User.h"
#include "Student.h"
#include <QVector>
#include <memory>

class Parent : public User
{
    private:
        QVector<std::shared_ptr<Student>> childrens;

    public:
        Parent(QString id, QVector<std::shared_ptr<Student>> students, QString password,
               QString name, QString surname);
        ~Parent() = default;
        [[nodiscard]] QVector<std::shared_ptr<Student>> getChildrens() const;
};
