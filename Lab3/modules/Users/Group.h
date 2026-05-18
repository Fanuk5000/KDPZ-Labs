#pragma once
#include <QVector>
#include "Student.h"

class Group
{
    private:
        QVector<std::shared_ptr<Student>> students;
        QVector<std::shared_ptr<Student>> teachers;
        QString groupID;

    public:
        Group(QVector<std::shared_ptr<Student>> students, QString groupID);
        ~Group() = default;
        void addStudent(const std::shared_ptr<Student>& student);
        [[nodiscard]] QVector<std::shared_ptr<Student>> getStudents() const;
        [[nodiscard]] QVector<std::shared_ptr<Student>> getTeachers() const;
        [[nodiscard]] QString getGroupID() const;
};
