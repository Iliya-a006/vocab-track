#include "word.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <memory>

Word::Word(QString t) : term(t)
{
    dateAdded = QDate::currentDate();
    nextReviewDate = dateAdded;
    correctReviews = 0;
}

std::map<QString, std::unique_ptr<Word>> Word::allWords;
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
        for (auto syn : wordObj["synonyms"].toArray())
            w->synonyms.push_back(syn.toString());
        for (auto tra : wordObj["translations"].toArray())
            w->translations.push_back(tra.toString());

        allWords.insert({w->term, std::move(w)});
    }
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
