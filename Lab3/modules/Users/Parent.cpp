#include "Parent.h"

Parent::Parent(QString id, QVector<std::shared_ptr<Student>> childrens, QString password,
               QString name, QString surname)
    : User(std::move(id), std::move(name), std::move(surname), std::move(password)),
      childrens(std::move(childrens))
{
}

QVector<std::shared_ptr<Student>> Parent::getChildrens() const { return childrens; }
