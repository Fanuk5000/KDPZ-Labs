#include <QCoreApplication>
#ifdef _WIN32
#include <windows.h>
#endif

#include "managers/DataManager.h"
#include "core/TestingEngine.h"
#include "ui/MainMenu.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    // Повертаємо підтримку UTF-8 для терміналу Windows
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    DataManager dataManager("users.json", "tests.json", "results.json");
    TestingEngine engine(&dataManager);

    MainMenu menu(&dataManager, &engine);
    menu.run();

    return 0;
}
