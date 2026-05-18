#pragma once

#include "../modules/Users/User.h"
#include "../modules/Tests/Test.h"
#include "../modules/Tests/Result.h"

class DataManager
{
    private:
        QString usersFilePath;
        QString testsFilePath;
        QString resultsFilePath;

    public:
        DataManager(QString usersPath, QString testsPath, QString resultsPath);

        QList<User> loadUsers() const;
        QList<Test> loadTests() const;
        bool saveResult(const Result& res) const;
        bool saveTest(const Test& test) const;
};
