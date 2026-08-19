#include "word.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <memory>
#include <QSettings>

Word::Word(QString t) : term(t)
{
    dateAdded = QDate::currentDate();
    nextReviewDate = dateAdded;
    correctReviews = 0;
    todayReviewed = {false, false};
}

std::map<QString, std::unique_ptr<Word>, CaseInsensitiveLess> Word::allWords;
void Word::loadWords()
{
    QFile file("words.json");
    if (!file.open(QIODevice::ReadOnly))
        return;
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();
    QJsonArray wordsArray = root["words"].toArray();

    for (const QJsonValue &val : wordsArray) {
        QJsonObject wordObj = val.toObject();
        std::unique_ptr<Word> w = std::make_unique<Word>(wordObj["term"].toString());

        w->partOfSpeech = wordObj["partOfSpeech"].toString();
        w->example = wordObj["example"].toString();
        w->correctReviews = wordObj["correctReviews"].toInt();
        w->dateAdded = QDate::fromString(wordObj["dateAdded"].toString(), "yyyy/MM/dd");
        w->nextReviewDate = QDate::fromString(wordObj["nextReviewDate"].toString(), "yyyy/MM/dd");
        w->todayReviewed.first = wordObj["todayReviewedFirst"].toBool();
        w->todayReviewed.second = wordObj["todayReviewedSecond"].toBool();

        for (auto syn : wordObj["synonyms"].toArray())
            w->synonyms.push_back(syn.toString());
        for (auto tra : wordObj["translations"].toArray())
            w->translations.push_back(tra.toString());

        allWords.insert({w->term, std::move(w)});
    }
}

void Word::saveFile()
{
    QJsonArray wordsArray;

    for (const auto& [key, w] : allWords) {
        QJsonObject wordObj;
        wordObj["term"] = w->term;
        wordObj["partOfSpeech"] = w->partOfSpeech;
        wordObj["example"] = w->example;
        wordObj["correctReviews"] = w->correctReviews;
        wordObj["dateAdded"] = w->dateAdded.toString("yyyy/MM/dd");
        wordObj["nextReviewDate"] = w->nextReviewDate.toString("yyyy/MM/dd");
        wordObj["todayReviewedFirst"] = w->todayReviewed.first;
        wordObj["todayReviewedSecond"] = w->todayReviewed.second;

        QJsonArray synonymsArray;
        for (const QString &syn : w->synonyms)
            synonymsArray.append(syn);
        wordObj["synonyms"] = synonymsArray;

        QJsonArray translationsArray;
        for (const QString &tra : w->translations)
            translationsArray.append(tra);
        wordObj["translations"] = translationsArray;

        wordsArray.append(wordObj);
    }

    QJsonObject root;
    root["words"] = wordsArray;
    QJsonDocument doc(root);

    QFile file("words.json");
    if (!file.open(QIODevice::WriteOnly))
        return;
    file.write(doc.toJson());
    file.close();
}

void Word::setCorrects(int c)
{
    if (c < 1){c = 1;}
    if (c > 6){c = 6;}
    correctReviews = c;

    switch (c) {
        case 1:
            nextReviewDate = QDate::currentDate().addDays(1);
            break;
        case 2:
            nextReviewDate = QDate::currentDate().addDays(2);
            break;
        case 3:
            nextReviewDate = QDate::currentDate().addDays(4);
            break;
        case 4:
            nextReviewDate = QDate::currentDate().addDays(7);
            break;
        case 5:
            nextReviewDate = QDate::currentDate().addDays(16);
            break;
        case 6:
            nextReviewDate = QDate::currentDate().addDays(60);
            break;
        default:
            break;
    }
}

void Word::resetDailyReviewStatusIfNeeded()
{
    QSettings settings("YourAppName", "VocabApp");
    QDate lastActiveDate = settings.value("lastActiveDate").toDate();
    QDate today = QDate::currentDate();

    if (lastActiveDate != today) {
        for (const auto& [key, w] : allWords) {
            w->setReviewed({false, false});
        }
        settings.setValue("lastActiveDate", today);
    }
}
