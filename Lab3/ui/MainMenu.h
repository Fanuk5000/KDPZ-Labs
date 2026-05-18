/**
 * @file MainMenu.h
 * @brief Клас інтерфейсу користувача.
 * 
 * MainMenu реалізує консольний інтерфейс для взаємодії зі студентом:
 * авторизація, перегляд доступних тестів та запуск сесії тестування.
 */

#pragma once

#include "../managers/DataManager.h"
#include "../core/TestingEngine.h"
#include <QTextStream>

class MainMenu
{
    private:
        DataManager* dataManager;     ///< Вказівник на менеджер даних
        TestingEngine* engine;        ///< Вказівник на двигун тестування
        QList<User> loadedUsers;      ///< Список завантажених користувачів
        QList<Test> loadedTests;      ///< Список завантажених тестів
        User* currentUser;            ///< Поточний авторизований користувач
        bool isRunning;               ///< Прапорець роботи циклу меню

        // Використання нативних потоків Qt для підтримки юнікоду
        QTextStream qout;             ///< Потік виводу
        QTextStream qin;              ///< Потік вводу

        /**
         * @brief Відображає екран авторизації та перевіряє облікові дані.
         */
        void showAuthScreen();

        /**
         * @brief Відображає головне меню після входу в систему.
         */
        void showMenu();

        /**
         * @brief Обробка вибору тесту зі списку доступних.
         */
        void handleTestSelection();

        /**
         * @brief Запуск процесу тестування для обраного тесту.
         * @param activeTest Вказівник на об'єкт обраного тесту.
         */
        void runTestSession(Test* activeTest);

    public:
        MainMenu(DataManager* dm, TestingEngine* eng);

        /**
         * @brief Очищення буфера вводу після зчитування значень.
         */
        void clearInputBuffer();

        /**
         * @brief Основний цикл роботи інтерфейсу.
         */
        void run();
};

