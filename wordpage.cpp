#include "wordpage.h"
#include "mainwindow.h"
#include "todaypage.h"

WordPage::WordPage(QWidget *parent)
    : Page(parent)
{
    this->background = ":/prefix1/images/Bg1";

    widgetsLoad();
    layoutLoad();
}

int WordPage::index = 0;
Word* WordPage::entryWord = nullptr;

void WordPage::refresh()
{
    if (entryWord){
        theWord = entryWord;
    }
    else{
        QWidget* widget = MainWindow::m_stack->widget(pageEnum::TODAYLIST);
        TodayPage* page = qobject_cast<TodayPage*>(widget);
        if (page){
            Words = page->getRemaining();
            theWord = Words[index];
        }
    }

    showCounter = 0;
    changeToShow();
}

void WordPage::changeToShow()
{
    termStack->setCurrentIndex(0);
    exampleStack->setCurrentIndex(0);
    synonymsStack->setCurrentIndex(0);
    translationsStack->setCurrentIndex(0);
    footButtonsStack->setCurrentIndex(0);
    editLabel->hide();
    showButton->show();
    editButton->show();
    POSLabel->hide();
    exampleLabel2->hide();
    synonymsArea->hide();
    translationsArea->hide();
    showCounter = 0;


    if (theWord){
        updateWidgets();
    }
}

void WordPage::changeToEdit()
{
    termStack->setCurrentIndex(1);
    exampleStack->setCurrentIndex(1);
    synonymsStack->setCurrentIndex(1);
    translationsStack->setCurrentIndex(1);
    footButtonsStack->setCurrentIndex(1);
    editLabel->show();
    showButton->hide();
    editButton->hide();

    if (theWord){
        termEdit->setText(theWord->getTerm());
        POSEdit->setCurrentText(theWord->getPOS());
        exampleEdit->setText(theWord->getExample());
        synonymEdit->setText("");
        translationEdit->setText("");
    }
}

void WordPage::widgetsLoad()
{
    termLabel = new QLabel(this);
    POSLabel = new QLabel(this);
    exampleLabel1 = new QLabel("Example", this);
    exampleLabel2 = new QLabel(this);
    synonymLabel = new QLabel("Synonyms", this);
    translationLabel = new QLabel("Translations", this);
    editLabel = new QLabel("Editing Word", this);

    synonymsArea = new QScrollArea(this);
    translationsArea = new QScrollArea(this);

    showButton = new QPushButton("Show", this);
    editButton = new QPushButton("Edit", this);
    exitButton = new QPushButton("Exit", this);
    knowButton = new QPushButton("Know It", this);
    dontKnowButton = new QPushButton("Don't Know", this);
    synonymButton = new QPushButton("Save", this);
    translationButton = new QPushButton("Save", this);
    saveButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);

    termEdit = new QLineEdit(this);
    exampleEdit = new QLineEdit(this);
    synonymEdit = new QLineEdit(this);
    translationEdit = new QLineEdit(this);

    POSEdit = new QComboBox(this);
    POSEdit->addItem("Noun");
    POSEdit->addItem("Verbe");
    POSEdit->addItem("Adjective");
    POSEdit->addItem("Adverbe");


    termLabel->setFixedSize(300, 40);
    POSLabel->setFixedSize(150, 30);
    exampleLabel1->setFixedSize(200, 25);
    exampleLabel2->setFixedHeight(40);
    synonymLabel->setFixedSize(200, 25);
    translationLabel->setFixedSize(200, 25);
    editLabel->setFixedSize(200, 30);

    synonymsArea->setFixedSize(320, 100);
    translationsArea->setFixedSize(320, 100);

    showButton->setFixedSize(120, 40);
    editButton->setFixedSize(120, 40);
    exitButton->setFixedSize(120, 40);
    knowButton->setFixedSize(150, 40);
    dontKnowButton->setFixedSize(150, 40);
    synonymButton->setFixedSize(80, 30);
    translationButton->setFixedSize(80, 30);
    saveButton->setFixedSize(120, 40);
    cancelButton->setFixedSize(120, 40);

    termEdit->setFixedSize(250, 30);
    exampleEdit->setFixedSize(250, 30);
    synonymEdit->setFixedSize(250, 30);
    translationEdit->setFixedSize(250, 30);

    POSEdit->setFixedSize(150, 30);

    termLabel->setAlignment(Qt::AlignCenter);
    POSLabel->setAlignment(Qt::AlignCenter);
    exampleLabel1->setAlignment(Qt::AlignCenter);
    exampleLabel2->setAlignment(Qt::AlignCenter);
    synonymLabel->setAlignment(Qt::AlignCenter);
    translationLabel->setAlignment(Qt::AlignCenter);
    editLabel->setAlignment(Qt::AlignCenter);


    connect(exitButton, &QPushButton::clicked, this, [](){
        entryWord = nullptr;
        MainWindow::changeStack(MainWindow::prevPage);
    });
    connect(editButton, &QPushButton::clicked, this, [this](){
        changeToEdit();
    });
    connect(showButton, &QPushButton::clicked, this, [this](){
        switch (showCounter) {
        case 0:
            POSLabel->show();
            ++showCounter;
            break;
        case 1:
            exampleLabel2->show();
            ++showCounter;
            break;
        case 2:
            synonymsArea->show();
            ++showCounter;
            break;
        case 3:
            translationsArea->show();
            ++showCounter;
            break;
        default:
            break;
        }
    });
    connect(knowButton, &QPushButton::clicked, this, [this](){
        if (MainWindow::prevPage != pageEnum::TODAYLIST){
            return;
        }

        theWord->setReviewed({true, true});
        Word::saveFile();
        index++;
        if (index == Words.size()){
            MainWindow::changeStack(pageEnum::TODAYLIST);
            return;
        }

        theWord = Words[index];
        updateWidgets();
        showCounter = 0;
        POSLabel->hide();
        exampleLabel2->hide();
        synonymsArea->hide();
        translationsArea->hide();
    });
    connect(dontKnowButton, &QPushButton::clicked, this, [this](){
        if (MainWindow::prevPage != pageEnum::TODAYLIST){
            return;
        }

        theWord->setReviewed({true, false});
        Word::saveFile();
        index++;
        if (index == Words.size()){
            MainWindow::changeStack(pageEnum::TODAYLIST);
            return;
        }

        theWord = Words[index];
        updateWidgets();
        showCounter = 0;
        POSLabel->hide();
        exampleLabel2->hide();
        synonymsArea->hide();
        translationsArea->hide();
    });
    connect(saveButton, &QPushButton::clicked, this, [this](){
        if (!termEdit->text().length()){
            return;
        }
        auto it = Word::allWords.find(termEdit->text());
        if (it != Word::allWords.end()){
            return;
        }
        theWord->setTerm(termEdit->text());
        theWord->setPOS(POSEdit->currentText());
        theWord->setExample(exampleEdit->text());

        Word::saveFile();
        changeToShow();
    });
    connect(cancelButton, &QPushButton::clicked, this, [this](){
        changeToShow();
    });
    connect(synonymButton, &QPushButton::clicked, this, [this](){
        if (!synonymEdit->text().length()){
            return;
        }
        for (auto syn : theWord->getSynonyms())
            if (syn == synonymEdit->text()){
                synonymEdit->setText("");
                return;
            }
        theWord->addSynonym(synonymEdit->text());
        Word::saveFile();
        synonymEdit->setText("");
    });
    connect(translationButton, &QPushButton::clicked, this, [this](){
        if (!translationEdit->text().length()){
            return;
        }
        for (auto tra : theWord->getTranslations())
            if(tra == translationEdit->text()){
                translationEdit->setText("");
                return;
            }
        theWord->addTranslation(translationEdit->text());
        Word::saveFile();
        translationEdit->setText("");
    });


    termLabel->setStyleSheet("QLabel {"
                             "   background-color: #f5ecd7;"
                             "   color: #1c3346;"
                             "   font-size: 26px;"
                             "   font-weight: bold;"
                             "   font-family: 'Trebuchet MS', 'Segoe UI';"
                             "   border-radius: 8px;"
                             "   padding: 4px 10px;"
                             "}");

    POSLabel->setStyleSheet("QLabel {"
                                            "   background-color: transparent;"
                                            "   color: white;"
                                            "   font-size: 18px;"
                                            "   font-family: 'Trebuchet MS', 'Segoe UI';"
                                            "}");

    QString fieldLabelStyle =
        "QLabel {"
        "   background-color: transparent;"
        "   color: #9fb8c9;"
        "   font-size: 14px;"
        "   font-family: 'Trebuchet MS', 'Segoe UI';"
        "}";
    exampleLabel1->setStyleSheet(fieldLabelStyle);
    synonymLabel->setStyleSheet(fieldLabelStyle);
    translationLabel->setStyleSheet(fieldLabelStyle);
    editLabel->setStyleSheet("QLabel {"
                             "   background-color: #f5ecd7;"
                             "   color: #1c3346;"
                             "   font-size: 18px;"
                             "   font-weight: bold;"
                             "   font-family: 'Trebuchet MS', 'Segoe UI';"
                             "   border-radius: 8px;"
                             "   padding: 4px 10px;"
                             "}");
    exampleLabel2->setStyleSheet("QLabel {"
                                 "   background-color: #1c3346;"
                                 "   color: white;"
                                 "   font-size: 20px;"
                                 "   font-weight: bold;"
                                 "   font-family: 'Trebuchet MS', 'Segoe UI';"
                                 "   border: 2px solid #5aa9d6;"
                                 "   border-radius: 10px;"
                                 "   padding: 6px 16px;"
                                 "}");

    QString lineEditStyle =
        "QLineEdit {"
        "   background-color: #1c3346;"
        "   color: #eaf4fb;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 8px;"
        "   padding: 4px 10px;"
        "   font-size: 14px;"
        "   font-family: 'Trebuchet MS', 'Segoe UI';"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #cfe3ee;"
        "}";
    termEdit->setStyleSheet(lineEditStyle);
    exampleEdit->setStyleSheet(lineEditStyle);
    synonymEdit->setStyleSheet(lineEditStyle);
    translationEdit->setStyleSheet(lineEditStyle);

    POSEdit->setStyleSheet(
        "QComboBox {"
        "   background-color: #1c3346;"
        "   color: #eaf4fb;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 8px;"
        "   padding: 4px 10px;"
        "   font-size: 14px;"
        "   font-family: 'Trebuchet MS', 'Segoe UI';"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #1c3346;"
        "   color: #eaf4fb;"
        "   selection-background-color: #5aa9d6;"
        "}"
        );

    QString primaryButtonStyle =
        "QPushButton {"
        "   background-color: #5aa9d6;"
        "   color: #0f1c26;"
        "   border: 2px solid #cfe3ee;"
        "   border-radius: 10px;"
        "   padding: 8px 20px;"
        "   font-size: 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #6fbce8;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #3f7094;"
        "}";
    showButton->setStyleSheet(primaryButtonStyle);
    knowButton->setStyleSheet(primaryButtonStyle);
    saveButton->setStyleSheet(primaryButtonStyle);

    QString secondaryButtonStyle =
        "QPushButton {"
        "   background-color: #274a63;"
        "   color: #eaf4fb;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 10px;"
        "   padding: 8px 20px;"
        "   font-size: 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #3f7094;"
        "   border: 2px solid #cfe3ee;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #16232f;"
        "}";
    editButton->setStyleSheet(secondaryButtonStyle);
    exitButton->setStyleSheet(secondaryButtonStyle);
    dontKnowButton->setStyleSheet(secondaryButtonStyle);
    cancelButton->setStyleSheet(secondaryButtonStyle);

    QString smallAddButtonStyle =
        "QPushButton {"
        "   background-color: #274a63;"
        "   color: #eaf4fb;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 8px;"
        "   padding: 4px 10px;"
        "   font-size: 13px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #3f7094;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #16232f;"
        "}";
    synonymButton->setStyleSheet(smallAddButtonStyle);
    translationButton->setStyleSheet(smallAddButtonStyle);

    synonymsArea->setStyleSheet(
        "QScrollArea {"
        "   background-color: #16232f;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 10px;"
        "}"
        "QAbstractScrollArea > QWidget#qt_scrollarea_viewport {"
        "   background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "   background-color: #1c3346;"
        "   width: 10px;"
        "   border-radius: 5px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background-color: #5aa9d6;"
        "   border-radius: 5px;"
        "   min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "   background-color: #6fbce8;"
        "}");
    translationsArea->setStyleSheet(synonymsArea->styleSheet());
}

void WordPage::updateWidgets()
{
    termLabel->setText(theWord->getTerm());
    POSLabel->setText( "(" + theWord->getPOS() + ")");
    exampleLabel2->setText(theWord->getExample());
    QFontMetrics fm(exampleLabel2->font());
    exampleLabel2->setFixedWidth(fm.horizontalAdvance(exampleLabel2->text()) + 80);

    QVBoxLayout* synLayout = new QVBoxLayout();
    QWidget* synWidget = new QWidget();
    for (auto s : theWord->getSynonyms()){
        QLabel* label = new QLabel(s);
        label->setStyleSheet("QLabel {"
                             "   background-color: #f5ecd7;"
                             "   color: #1c3346;"
                             "   font-size: 15px;"
                             "   font-weight: bold;"
                             "   font-family: 'Trebuchet MS', 'Segoe UI';"
                             "   border-radius: 8px;"
                             "   padding: 4px 10px;"
                             "}");
        synLayout->addWidget(label);
    }
    synWidget->setAutoFillBackground(false);
    synWidget->setStyleSheet("background-color: transparent;");
    synWidget->setLayout(synLayout);
    QWidget* oldSynWidget = synonymsArea->takeWidget();
    if (oldSynWidget)
        oldSynWidget->deleteLater();
    synonymsArea->setWidget(synWidget);


    QVBoxLayout* tranLayout = new QVBoxLayout();
    QWidget* tranWidget = new QWidget();
    for (auto t : theWord->getTranslations()){
        QLabel* label = new QLabel(t);
        label->setStyleSheet("QLabel {"
                             "   background-color: #f5ecd7;"
                             "   color: #1c3346;"
                             "   font-size: 15px;"
                             "   font-weight: bold;"
                             "   font-family: 'Trebuchet MS', 'Segoe UI';"
                             "   border-radius: 8px;"
                             "   padding: 4px 10px;"
                             "}");
        label->adjustSize();
        tranLayout->addWidget(label);
    }
    tranWidget->setAutoFillBackground(false);
    tranWidget->setStyleSheet("background-color: transparent;");
    tranWidget->setLayout(tranLayout);
    QWidget* oldTranWidget = translationsArea->takeWidget();
    if (oldTranWidget)
        oldTranWidget->deleteLater();
    translationsArea->setWidget(tranWidget);
}

void WordPage::layoutLoad()
{
    termStack = new QStackedLayout;
    exampleStack = new QStackedLayout;
    synonymsStack = new QStackedLayout;
    translationsStack = new QStackedLayout;
    footButtonsStack = new QStackedLayout;

    outerLayout = new QVBoxLayout();
    topLayout = new QHBoxLayout();
    termLayout = new QHBoxLayout();
    exampleLayout1 = new QHBoxLayout();
    exampleLayout2 = new QHBoxLayout();
    titlesLayout = new QHBoxLayout();
    areasLayout = new QHBoxLayout();
    buttonsRow1 = new QHBoxLayout();
    buttonsRow2 = new QHBoxLayout();


    QHBoxLayout* termInnerLayout1 = new QHBoxLayout;
    QHBoxLayout* termInnerLayout2 = new QHBoxLayout;
    QWidget* termWidget1 = new QWidget;
    QWidget* termWidget2 = new QWidget;
    termInnerLayout1->addStretch(1);
    termInnerLayout1->addWidget(termLabel);
    termInnerLayout1->addWidget(POSLabel);
    termInnerLayout1->addStretch(1);
    termWidget1->setLayout(termInnerLayout1);
    termInnerLayout2->addWidget(termEdit);
    termInnerLayout2->addWidget(POSEdit);
    termWidget2->setLayout(termInnerLayout2);
    termStack->addWidget(termWidget1);
    termStack->addWidget(termWidget2);

    QHBoxLayout* exampleInnerLayout1 = new QHBoxLayout;
    QHBoxLayout* exampleInnerLayout2 = new QHBoxLayout;
    QWidget* exampleWidget1 = new QWidget;
    QWidget* exampleWidget2 = new QWidget;
    exampleInnerLayout1->addWidget(exampleLabel2);
    exampleWidget1->setLayout(exampleInnerLayout1);
    exampleInnerLayout2->addWidget(exampleEdit);
    exampleWidget2->setLayout(exampleInnerLayout2);
    exampleStack->addWidget(exampleWidget1);
    exampleStack->addWidget(exampleWidget2);

    QHBoxLayout* synonymsInnerLayout1 = new QHBoxLayout;
    QHBoxLayout* synonymsInnerLayout2 = new QHBoxLayout;
    QWidget* synonymsWidget1 = new QWidget;
    QWidget* synonymsWidget2 = new QWidget;
    synonymsInnerLayout1->addWidget(synonymsArea);
    synonymsWidget1->setLayout(synonymsInnerLayout1);
    synonymsInnerLayout2->addWidget(synonymEdit);
    synonymsInnerLayout2->addWidget(synonymButton);
    synonymsWidget2->setLayout(synonymsInnerLayout2);
    synonymsStack->addWidget(synonymsWidget1);
    synonymsStack->addWidget(synonymsWidget2);

    QHBoxLayout* translationsInnerLayout1 = new QHBoxLayout;
    QHBoxLayout* translationsInnerLayout2 = new QHBoxLayout;
    QWidget* translationsWidget1 = new QWidget;
    QWidget* translationsWidget2 = new QWidget;
    translationsInnerLayout1->addWidget(translationsArea);
    translationsWidget1->setLayout(translationsInnerLayout1);
    translationsInnerLayout2->addWidget(translationEdit);
    translationsInnerLayout2->addWidget(translationButton);
    translationsWidget2->setLayout(translationsInnerLayout2);
    translationsStack->addWidget(translationsWidget1);
    translationsStack->addWidget(translationsWidget2);

    QHBoxLayout* footInnerLayout1 = new QHBoxLayout;
    QHBoxLayout* footInnerLayout2 = new QHBoxLayout;
    QWidget* footWidget1 = new QWidget;
    QWidget* footWidget2 = new QWidget;
    footInnerLayout1->addStretch(1);
    footInnerLayout1->addWidget(exitButton);
    footInnerLayout1->addStretch(4);
    footInnerLayout1->addWidget(knowButton);
    footInnerLayout1->addWidget(dontKnowButton);
    footInnerLayout1->addStretch(1);
    footWidget1->setLayout(footInnerLayout1);
    footInnerLayout2->addStretch(1);
    footInnerLayout2->addWidget(cancelButton);
    footInnerLayout2->addStretch(4);
    footInnerLayout2->addWidget(saveButton);
    footInnerLayout2->addStretch(1);
    footWidget2->setLayout(footInnerLayout2);
    footButtonsStack->addWidget(footWidget1);
    footButtonsStack->addWidget(footWidget2);


    topLayout->addWidget(editLabel);
    termLayout->addLayout(termStack);
    exampleLayout1->addWidget(exampleLabel1);
    exampleLayout2->addLayout(exampleStack);

    titlesLayout->addStretch(1);
    titlesLayout->addWidget(synonymLabel);
    titlesLayout->addStretch(1);
    titlesLayout->addWidget(translationLabel);
    titlesLayout->addStretch(1);

    areasLayout->addStretch(1);
    areasLayout->addLayout(synonymsStack);
    areasLayout->addStretch(1);
    areasLayout->addLayout(translationsStack);
    areasLayout->addStretch(1);

    buttonsRow1->addStretch(1);
    buttonsRow1->addWidget(editButton);
    buttonsRow1->addStretch(3);
    buttonsRow1->addWidget(showButton);
    buttonsRow1->addStretch(1);

    buttonsRow2->addLayout(footButtonsStack);

    outerLayout->addStretch(1);
    outerLayout->addLayout(topLayout);
    outerLayout->addLayout(termLayout);
    outerLayout->addStretch(1);
    outerLayout->addLayout(exampleLayout1);
    outerLayout->addLayout(exampleLayout2);
    outerLayout->addStretch(1);
    outerLayout->addLayout(titlesLayout);
    outerLayout->addLayout(areasLayout);
    outerLayout->addStretch(1);
    outerLayout->addLayout(buttonsRow1);
    outerLayout->addLayout(buttonsRow2);
    outerLayout->addStretch(1);

    this->setLayout(outerLayout);
}

WordPage::~WordPage()
{

}




