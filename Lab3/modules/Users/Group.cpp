#include "Group.h"

Group::Group(QVector<std::shared_ptr<Student>> students, QString groupID) :
    students(std::move(students)), groupID(std::move(groupID))
{
}

void Group::addStudent(const std::shared_ptr<Student>& student)
{
    for (const auto& s : students)
    {
        if (s && s->getId() == student->getId())
        {
            return; // already present
        }
    }
    students.append(student);
}

QString Group::getGroupID() const
{
    return this->groupID;
}

QVector<std::shared_ptr<Student>> Group::getStudents() const { return this->students; }
QVector<std::shared_ptr<Student>> Group::getTeachers() const { return this->teachers; }
