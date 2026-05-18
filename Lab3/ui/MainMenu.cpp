#include "MainMenu.h"
#include <iostream>
#include <string>
#include <limits>
#include <QStringList>

MainMenu::MainMenu(DataManager* dm, TestingEngine* eng)
    : dataManager(dm), engine(eng), currentUser(nullptr), isRunning(true)
{
    // Load data once upon initialization
    loadedUsers = dataManager->loadUsers();
    loadedTests = dataManager->loadTests();
}

void MainMenu::clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void MainMenu::run()
{
    while (isRunning)
    {
        if (!currentUser)
        {
            showAuthScreen();
        }
        else
        {
            showMenu();
        }
    }
}

void MainMenu::showAuthScreen()
{
    std::cout << "========================================\n";
    std::cout << "      OFFLINE STUDENT TESTING SYSTEM    \n";
    std::cout << "========================================\n\n";
    std::cout << "--- Authorization ---\n";

    std::cout << "Enter your student ID (type 'exit' to quit): ";
    std::string idInput;
    std::cin >> idInput;

    if (idInput == "exit")
    {
        isRunning = false;
        return;
    }

    std::cout << "Enter Name: ";
    std::string nameInput;
    std::cin >> nameInput;

    // Note: Based on your authenticate method, 'surname' is checked against 'login'
    std::cout << "Enter Login: ";
    std::string surnameInput;
    std::cin >> surnameInput;

    std::cout << "Enter Password: ";
    std::string passwordInput;
    std::cin >> passwordInput;

    // Iterate through loaded users and use your 4-parameter authenticate method
    for (int i = 0; i < loadedUsers.size(); ++i)
    {
        if (loadedUsers[i].authenticate(
            QString::fromStdString(idInput),
            QString::fromStdString(nameInput),
            QString::fromStdString(surnameInput),
            QString::fromStdString(passwordInput)))
        {
            currentUser = &loadedUsers[i];
            break;
        }
    }

    if (currentUser)
    {
        std::cout << "\n[Success] Welcome, " << currentUser->getName().toStdString() << "!\n";
    }
    else
    {
        std::cout << "\n[Error] Invalid credentials. Please try again.\n\n";
    }
}

void MainMenu::showMenu()
{
    std::cout << "\n--- Main Menu ---\n";
    std::cout << "1. Take Available Test\n";
    std::cout << "2. Logout\n";
    std::cout << "3. Exit Application\n";
    std::cout << "Select an option: ";

    int choice;
    std::cin >> choice;

    if (std::cin.fail())
    {
        clearInputBuffer();
        std::cout << "Invalid input. Please enter a number.\n";
        return;
    }

    switch (choice)
    {
    case 1:
        handleTestSelection();
        break;
    case 2:
        currentUser = nullptr;
        std::cout << "\nLogging out...\n\n";
        break;
    case 3:
        currentUser = nullptr;
        isRunning = false;
        std::cout << "\nExiting offline testing system. Goodbye.\n";
        break;
    default:
        std::cout << "Invalid option. Please try again.\n";
        break;
    }
}

void MainMenu::handleTestSelection()
{
    if (loadedTests.isEmpty())
    {
        std::cout << "\nNo tests currently available in the jsons.\n";
        return;
    }

    std::cout << "\n--- Test Selection ---\n";
    for (int i = 0; i < loadedTests.size(); ++i)
    {
        std::cout << "[" << (i + 1) << "] " << loadedTests[i].getTitle().toStdString()
            << " (" << loadedTests[i].getDurationMinutes() << " minutes)\n";
    }
    std::cout << "[0] Cancel\n";
    std::cout << "Select test: ";

    int testChoice;
    std::cin >> testChoice;

    if (std::cin.fail())
    {
        clearInputBuffer();
        std::cout << "Invalid input.\n";
        return;
    }

    if (testChoice > 0 && testChoice <= loadedTests.size())
    {
        runTestSession(&loadedTests[testChoice - 1]);
    }
}

void MainMenu::runTestSession(Test* activeTest)
{
    engine->initializeSession(currentUser->getId(), activeTest);
    engine->startSession();

    std::cout << "\n========================================\n";
    std::cout << " SESSION STARTED: " << activeTest->getTitle().toStdString() << "\n";
    std::cout << "========================================\n";

    const QList<Question>& questions = activeTest->getQuestions();

    clearInputBuffer();

    for (int i = 0; i < questions.size(); ++i)
    {
        const Question& q = questions[i];
        std::cout << "\n[Question " << (i + 1) << " of " << questions.size() << "]\n";
        std::cout << "Category: " << q.getCategory().toStdString() << "\n";
        std::cout << "Points: " << q.getPoints() << "\n";
        std::cout << "Text: " << q.getText().toStdString() << "\n\n";

        const QList<AnswerOption>& options = q.getOptions();
        for (int j = 0; j < options.size(); ++j)
        {
            std::cout << "  [" << options[j].getOptionId().toStdString() << "] "
                << options[j].getText().toStdString() << "\n";
        }

        std::cout << "\nEnter your answer ID(s) [Separate by space]: ";

        // ЗВІДСИ ВИДАЛЕНО clearInputBuffer();

        std::string answerInput;
        std::getline(std::cin, answerInput);

        // 2. ДОДАЄМО .trimmed(), щоб прибрати приховані \r та зайві пробіли з кінця
        QString qStrInput = QString::fromStdString(answerInput).trimmed();

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
        QStringList selectedOptionIds = qStrInput.split(" ", Qt::SkipEmptyParts);
#else
        QStringList selectedOptionIds = qStrInput.split(" ", QString::SkipEmptyParts);
#endif

        engine->selectAnswer(q.getQuestionId(), selectedOptionIds);
        std::cout << ">> System: Local auto-save triggered...\n";
    }

    std::cout << "\n========================================\n";
    std::cout << " TEST COMPLETED. PROCESSING RESULTS...\n";
    std::cout << "========================================\n";

    QObject::disconnect(engine, &TestingEngine::testFinished, nullptr, nullptr);
    QObject::connect(engine, &TestingEngine::testFinished, [](const Result& result)
    {
        std::cout << ">> Final Score: " << result.getScore() << "\n";
        std::cout << ">> Exporting results to structured JSON format... Done.\n";
    });

    engine->finishTest();
}
