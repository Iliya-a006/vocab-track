#ifndef TODAYPAGE_H
#define TODAYPAGE_H
#include "page.h"
#include "word.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <qboxlayout.h>
class TodayPage : public Page
{
    Q_OBJECT
public:
    explicit TodayPage(QWidget *parent = nullptr);
    ~TodayPage();
    void refresh() override;
private:
    QPushButton* startButton;
    QPushButton* backButton;
    QLabel* topLabel;
    QScrollArea* scrollArea;
    QVector<Word*> remainingWords;
    QVector<Word*> reviewedWords;
    void setupUI();
    void updateList();
    QVBoxLayout *setupList();

public:
    QVector<Word*> getRemaining(){return remainingWords;}
};
#endif // TODAYPAGE_H







