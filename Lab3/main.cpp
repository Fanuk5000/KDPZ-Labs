/**
 * @file main.cpp
 * @brief Точка входу в систему тестування.
 * 
 * Цей файл відповідає за ініціалізацію основних компонентів системи:
 * менеджера даних, двигуна тестування та головного меню.
 */

#include <QCoreApplication>
#ifdef _WIN32
#include <windows.h>
#endif

#include "managers/DataManager.h"
#include "core/TestingEngine.h"
#include "ui/MainMenu.h"

int main(int argc, char* argv[])
{
    // Ініціалізація консольного додатка Qt
    QCoreApplication a(argc, argv);

    // Встановлення кодування UTF-8 для коректного відображення кирилиці в консолі Windows
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // Ініціалізація менеджера даних із вказанням шляхів до JSON-файлів
    DataManager dataManager("users.json", "tests.json", "results.json");
    
    // Створення двигуна тестування, що використовує менеджер даних для збереження результатів
    TestingEngine engine(&dataManager);

    // Створення та запуск головного меню користувача
    MainMenu menu(&dataManager, &engine);
    menu.run();

    return 0;
}
