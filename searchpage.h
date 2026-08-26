#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include "page.h"
#include "word.h"
#include <QWidget>
#include <qboxlayout.h>
#include <qlabel.h>
#include <QLineEdit>
#include <qpushbutton.h>
#include <qscrollarea.h>

class SearchPage : public Page
{
    Q_OBJECT

public:
    explicit SearchPage(QWidget *parent = nullptr);
    ~SearchPage();

    void refresh() override;

private:
    QLabel* topLabel;
    QLineEdit* searchEdit;
    QPushButton* searchButton;
    QPushButton* backButton;
    QScrollArea* scrollArea;

    QVBoxLayout* outterLayout;
    QVBoxLayout* listLayout;
    QWidget* listWidget;

    QVector<Word*> words;
    int maxListHeigth;

    void refreshResults();

};

#endif // SEARCHPAGE_H






