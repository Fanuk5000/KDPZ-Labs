#pragma once

#include "../managers/DataManager.h"
#include "../core/TestingEngine.h"

class MainMenu
{
    private:
        DataManager* dataManager;
        TestingEngine* engine;
        QList<User> loadedUsers;
        QList<Test> loadedTests;
        User* currentUser;
        bool isRunning;

        // Use Qt's native text streams instead of iostream
        QTextStream qout;
        QTextStream qin;

        void showAuthScreen();
        void showMenu();
        void handleTestSelection();
        void runTestSession(Test* activeTest);

    public:
        MainMenu(DataManager* dm, TestingEngine* eng);
        void clearInputBuffer();
        void run();
};

