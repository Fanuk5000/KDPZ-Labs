#include "DataManager.h"

#include <QString>
#include <QList>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QDebug>
#include "iostream"

DataManager::DataManager(QString usersPath, QString testsPath, QString resultsPath)
    : usersFilePath(std::move(usersPath)),
      testsFilePath(std::move(testsPath)),
      resultsFilePath(std::move(resultsPath))
{
}

QList<User> DataManager::loadUsers() const
{
    QList<User> users;
    QFile file(usersFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open users file:" << usersFilePath;
        return users;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isArray())
    {
        QJsonArray arr = doc.array();
        for (const QJsonValue& val : arr)
        {
            QJsonObject obj = val.toObject();
            users.append(User(
                obj["id"].toString(),
                obj["name"].toString(),
                obj["login"].toString(),
                obj["passwordHash"].toString()
            ));
        }
    }
    return users;
}

QList<Test> DataManager::loadTests() const
{
    QList<Test> tests;
    QFile file(testsFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "[System Error] Could not open tests file: " << testsFilePath.toStdString() <<
            "\n";
        return tests;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    // This will catch BOM issues, hidden characters, or missing commas
    if (parseError.error != QJsonParseError::NoError)
    {
        std::cout << "[System Error] Failed to parse tests.json: "
            << parseError.errorString().toStdString()
            << " at offset " << parseError.offset << "\n";
        return tests;
    }

    if (!doc.isArray())
    {
        std::cout << "[System Error] tests.json is formatted incorrectly (must be a JSON array).\n";
        return tests;
    }

    QJsonArray testArray = doc.array();
    for (const QJsonValue& testVal : testArray)
    {
        QJsonObject testObj = testVal.toObject();

        QList<QString> groupIds;
        QJsonArray groupsArray = testObj["assignedGroupIds"].toArray();
        for (const QJsonValue& groupVal : groupsArray)
        {
            groupIds.append(groupVal.toString());
        }

        QList<Question> questions;
        QJsonArray questionsArray = testObj["questions"].toArray();


        for (const QJsonValue& questionVal : questionsArray)
        {
            QJsonObject qObj = questionVal.toObject();

            QStringList correctIds;
            QJsonArray correctIdsArray = qObj["correctOptionIds"].toArray();
            for (const QJsonValue& idVal : correctIdsArray)
            {
                correctIds.append(idVal.toString());
            }

            // НОВИЙ БЛОК: Читаємо варіанти відповідей
            QList<AnswerOption> answerOptions;
            QJsonArray optionsArray = qObj["options"].toArray();
            for (const QJsonValue& optVal : optionsArray)
            {
                QJsonObject oObj = optVal.toObject();
                answerOptions.append(AnswerOption(
                    oObj["optionId"].toString(),
                    oObj["text"].toString(),
                    oObj["isCorrect"].toBool()
                ));
            }

            // Передаємо answerOptions у конструктор
            questions.append(Question(
                qObj["questionId"].toString(),
                qObj["category"].toString(),
                qObj["text"].toString(),
                qObj["points"].toDouble(),
                correctIds,
                answerOptions
            ));
        }

        tests.append(Test(
            testObj["testId"].toString(),
            testObj["title"].toString(),
            testObj["durationMinutes"].toInt(),
            testObj["maxAttempts"].toInt(),
            groupIds,
            questions
        ));
    }

    std::cout << ">> System: Successfully loaded " << tests.size() << " tests from database.\n";
    return tests;
}

bool DataManager::saveResult(const Result& res) const
{
    QFile file(resultsFilePath);
    QJsonArray resultsArray;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray())
        {
            resultsArray = doc.array();
        }
        file.close();
    }

    QJsonObject resultObj;
    resultObj["resultId"] = res.getResultId();
    resultObj["sessionId"] = res.getSessionId();
    resultObj["score"] = res.getScore();
    resultObj["timestamp"] = res.getTimestamp().toString(Qt::ISODate);

    resultsArray.append(resultObj);
    QJsonDocument newDoc(resultsArray);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(newDoc.toJson());
        file.close();
        qDebug() << "Result saved successfully to" << resultsFilePath;
        return true;
    }

    qWarning() << "Failed to write result to" << resultsFilePath;
    return false;
}

bool DataManager::saveTest(const Test& test) const
{
    QFile file(testsFilePath);
    QJsonArray testsArray;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray())
        {
            testsArray = doc.array();
        }
        file.close();
    }

    QJsonObject testObj;
    testObj["testId"] = test.getTestId();
    testObj["title"] = test.getTitle();
    testObj["durationMinutes"] = test.getDurationMinutes();
    testObj["maxAttempts"] = test.getMaxAttempts();

    QJsonArray groupsArray;
    for (const QString& groupId : test.getAssignedGroupIds())
    {
        groupsArray.append(groupId);
    }
    testObj["assignedGroupIds"] = groupsArray;

    QJsonArray questionsArray;
    for (const Question& q : test.getQuestions())
    {
        QJsonObject qObj;
        qObj["questionId"] = q.getQuestionId();
        qObj["category"] = q.getCategory();
        qObj["text"] = q.getText();
        qObj["points"] = q.getPoints();

        // Serialize the correct IDs into a JSON array
        QJsonArray correctIdsArray;
        for (const QString& id : q.getCorrectOptionIds())
        {
            correctIdsArray.append(id);
        }
        qObj["correctOptionIds"] = correctIdsArray;

        questionsArray.append(qObj);
    }
    testObj["questions"] = questionsArray;

    testsArray.append(testObj);
    QJsonDocument newDoc(testsArray);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(newDoc.toJson());
        file.close();
        qDebug() << "Test saved successfully to" << testsFilePath;
        return true;
    }

    qWarning() << "Failed to write test to" << testsFilePath;
    return false;
}
