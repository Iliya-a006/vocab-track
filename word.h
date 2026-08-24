#ifndef WORD_H
#define WORD_H

#include <qobject.h>
#include <QDate>
#include <map>

struct CaseInsensitiveLess {
    bool operator()(const QString& a, const QString& b) const {
        return a.toLower() < b.toLower();
    }
};

class Word
{
public:
    Word(QString t);

    static std::map<QString, std::unique_ptr<Word>, CaseInsensitiveLess> allWords;
    static void loadWords();
    static void saveFile();
    static void resetDailyReviewStatusIfNeeded();

private:
    QString term;
    QString partOfSpeech;
    QString example;
    QVector<QString> synonyms;
    QVector<QString> translations;

    QDate dateAdded;
    QDate nextReviewDate;
    int correctReviews;
    std::pair<bool, bool> todayReviewed;

public:
    QString getTerm(){return term;}
    QString getPOS(){return partOfSpeech;}
    QString getExample(){return example;}
    QVector<QString> getSynonyms(){return synonyms;}
    QVector<QString> getTranslations(){return translations;}
    QDate getDateAdded(){return dateAdded;}
    QDate getNextDate(){return nextReviewDate;}
    int getCorrects(){return correctReviews;}
    std::pair<bool, bool> getReviewed() {return todayReviewed;}

    void setTerm(QString t){term = t;}
    void setPOS(QString pos){partOfSpeech = pos;}
    void setExample(QString e){example = e;}
    void addSynonym(QString s){synonyms.push_back(s);}
    void addTranslation(QString t){translations.push_back(t);}
    void setCorrects(int c);
    void setReviewed(std::pair<bool, bool> r){todayReviewed = r;}

};

#endif // WORD_H







