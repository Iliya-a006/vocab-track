#ifndef DIFFICULTYLISTPAGE_H
#define DIFFICULTYLISTPAGE_H

#include "page.h"
#include "verticalsortlabel.h"
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>

class Word;

class DifficultyListPage : public Page
{
    Q_OBJECT
public:
    explicit DifficultyListPage(QWidget *parent = nullptr);
    ~DifficultyListPage();

    void refresh() override;

private:
    void refreshList();
    void loadList();

    QScrollArea *scrollArea;
    QPushButton *backButton;
    QWidget *listWidget;
    VerticalSortLabel *sortLabel;

    QVBoxLayout *listLayout;
    QVBoxLayout *VLayout;
    QHBoxLayout *areaLayout;
    QHBoxLayout *buttonLayout;

    // snapshot of Word*, sorted by correctReviews ascending (hardest first)
    // rebuilt every refreshList() call since correctReviews can change between visits
    std::vector<Word*> sortedWords;
    size_t loadIndex;
};

#endif // DIFFICULTYLISTPAGE_H
