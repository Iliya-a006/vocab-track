#ifndef WORDPAGE_H
#define WORDPAGE_H

#include <QWidget>
#include <qboxlayout.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include "page.h"
#include "word.h"
#include <QStackedLayout>

class WordPage : public Page
{
    Q_OBJECT

public:
    explicit WordPage(QWidget *parent = nullptr);
    ~WordPage();

    void refresh() override;

    static int index;

private:
    void layoutLoad();
    void widgetsLoad();
    void updateWidgets();
    void changeToEdit();
    void changeToShow();

    Word* theWord;
    QVector<Word*> Words;
    int showCounter;

    QLabel* termLabel;
    QLabel* POSLabel;
    QLabel* exampleLabel1;
    QLabel* exampleLabel2;
    QLabel* synonymLabel;
    QLabel* translationLabel;
    QLabel* editLabel;

    QScrollArea* synonymsArea;
    QScrollArea* translationsArea;

    QPushButton* showButton;
    QPushButton* editButton;
    QPushButton* exitButton;
    QPushButton* knowButton;
    QPushButton* dontKnowButton;
    QPushButton* synonymButton;
    QPushButton* translationButton;
    QPushButton* saveButton;
    QPushButton* cancelButton;

    QLineEdit* termEdit;
    QLineEdit* exampleEdit;
    QLineEdit* synonymEdit;
    QLineEdit* translationEdit;
    QComboBox* POSEdit;

    QVBoxLayout* outerLayout;
    QHBoxLayout* topLayout;
    QHBoxLayout* termLayout;
    QHBoxLayout* exampleLayout1;
    QHBoxLayout* exampleLayout2;
    QHBoxLayout* titlesLayout;
    QHBoxLayout* areasLayout;
    QHBoxLayout* buttonsRow1;
    QHBoxLayout* buttonsRow2;

    QStackedLayout* termStack;
    QStackedLayout* exampleStack;
    QStackedLayout* synonymsStack;
    QStackedLayout* translationsStack;
    QStackedLayout* footButtonsStack;
};

#endif // WORDPAGE_H








