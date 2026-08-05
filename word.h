#ifndef WORD_H
#define WORD_H

#include <qobject.h>
#include <QDate>
#include <map>

class Word
{
public:
    Word(QString t);

    static std::map<QString, std::unique_ptr<Word>> allWords;
    static void loadWords();

private:
    QString term;
    QString partOfSpeech;
    QString example;
    QVector<QString> synonyms;
    QVector<QString> translations;

    QDate dateAdded;
    QDate nextReviewDate;
    int correctReviews;

public:
    QString getTerm(){return term;}
    QString getPOS(){return partOfSpeech;}
    QString getExample(){return example;}
    QVector<QString> getSynonyms(){return synonyms;}
    QVector<QString> getTranslations(){return translations;}
    QDate getDateAdded(){return dateAdded;}
    QDate getNextDate(){return nextReviewDate;}
    int getCorrects(){return correctReviews;}

    void setTerm(QString t){term = t;}
    void setPOS(QString pos){partOfSpeech = pos;}
    void setExample(QString e){example = e;}
    void addSynonym(QString s){synonyms.push_back(s);}
    void addTranslation(QString t){translations.push_back(t);}
    void setCorrects(int c);

};

#endif // WORD_H







