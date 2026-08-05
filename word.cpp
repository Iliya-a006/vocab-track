#include "word.h"

Word::Word(QString t) : term(t)
{
    dateAdded = QDate::currentDate();
    nextReviewDate = dateAdded;
    correctReviews = 0;
}

QVector<Word> allWords;

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
