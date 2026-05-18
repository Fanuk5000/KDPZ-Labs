/**
 * @file TestingEngine.h
 * @brief Ядро системи тестування.
 * 
 * Клас TestingEngine реалізує логіку керування сесією тестування,
 * включаючи відстеження часу, керування станами та обробку відповідей.
 */

#pragma once

#include <QTimer>
#include <QList>
#include <QString>
#include "../modules/Tests/TestSession.h"
#include "../managers/DataManager.h"

class TestingEngine : public QObject
{
        Q_OBJECT

    public:
        /**
         * @brief Стани сесії тестування.
         * Відповідають діаграмі станів (State Machine Diagram).
         */
        enum class SessionState
        {
            Created,      ///< Сесію створено
            Initialized,  ///< Дані завантажено, готова до старту
            Active,       ///< Тест триває, таймер запущено
            Completed,    ///< Час вийшов або користувач завершив тест
            Evaluated,    ///< Результати підраховано
            Saved         ///< Результати збережено в базу даних
        };

        Q_ENUM(SessionState)

    private:
        SessionState currentState;   ///< Поточний стан системи
        TestSession* session;        ///< Поточна сесія (дані про проходження)
        Test* activeTest;            ///< Тест, який зараз проходить користувач
        DataManager* dataManager;    ///< Менеджер для роботи з даними

        QTimer* countdownTimer;      ///< Таймер зворотного відліку
        QTimer* autoSaveTimer;       ///< Таймер автоматичного збереження
        int remainingSeconds;        ///< Залишок часу в секундах

        /**
         * @brief Обрані відповіді користувача.
         * Ключ - ID питання, значення - список ID обраних варіантів.
         */
        QMap<QString, QList<QString>> currentAnswers;

        /**
         * @brief Змінює стан системи та сповіщає підписників.
         */
        void changeState(SessionState newState);

    public:
        TestingEngine(DataManager* db, QObject* parent = nullptr);
        ~TestingEngine() override;

        /**
         * @brief Підготовка сесії для конкретного студента та тесту.
         */
        void initializeSession(const QString& studentId, Test* test);

        /**
         * @brief Запуск тестування та таймерів.
         */
        void startSession();

        /**
         * @brief Реєстрація відповіді користувача.
         * Викликає логіку автозбереження відповідно до діаграми активності.
         */
        void selectAnswer(const QString& questionId, const QList<QString>& selectedIds);

        [[nodiscard]] SessionState getState() const;

    public slots:
        /**
         * @brief Завершення тесту (за запитом або за таймером).
         */
        void finishTest();

    private slots:
        void onTick();               ///< Обробка кожної секунди таймера
        void performAutoSave();      ///< Виконання автозбереження

    signals:
        void stateChanged(TestingEngine::SessionState newState); ///< Сигнал про зміну стану
        void timeUpdated(int secondsLeft);                       ///< Сигнал про оновлення часу
        void testFinished(const Result& result);                 ///< Сигнал про завершення
        void autoSaveCompleted();                                ///< Сигнал про успішне автозбереження
};
