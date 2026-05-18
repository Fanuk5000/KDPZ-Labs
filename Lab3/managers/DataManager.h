/**
 * @file DataManager.h
 * @brief Менеджер керування даними.
 * 
 * Клас DataManager відповідає за взаємодію з файловою системою:
 * завантаження списку користувачів, тестів та збереження результатів.
 */

#pragma once

#include "../modules/Users/User.h"
#include "../modules/Tests/Test.h"
#include "../modules/Tests/Result.h"

class DataManager
{
    private:
        QString usersFilePath;   ///< Шлях до файлу з користувачами
        QString testsFilePath;   ///< Шлях до файлу з тестами
        QString resultsFilePath; ///< Шлях до файлу для збереження результатів

    public:
        /**
         * @brief Конструктор менеджера даних.
         * @param usersPath Шлях до JSON з користувачами.
         * @param testsPath Шлях до JSON з тестами.
         * @param resultsPath Шлях до JSON для результатів.
         */
        DataManager(QString usersPath, QString testsPath, QString resultsPath);

        /**
         * @brief Завантажує всіх зареєстрованих користувачів.
         * @return Список об'єктів User.
         */
        QList<User> loadUsers() const;

        /**
         * @brief Завантажує доступні тести.
         * @return Список об'єктів Test.
         */
        QList<Test> loadTests() const;

        /**
         * @brief Зберігає результат проходження тесту у файл.
         * @param res Об'єкт з результатом.
         * @return true, якщо збереження успішне.
         */
        bool saveResult(const Result& res) const;

        /**
         * @brief Зберігає або оновлює дані тесту.
         * @param test Об'єкт тесту.
         * @return true, якщо збереження успішне.
         */
        bool saveTest(const Test& test) const;
};
