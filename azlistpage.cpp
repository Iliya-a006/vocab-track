#include "azlistpage.h"
#include "mainwindow.h"
#include "screensize.h"
#include "word.h"
#include <QScrollBar>
#include "wordpage.h"

AZListPage::AZListPage(QWidget *parent)
    : Page(parent)
    , listWidget(nullptr)
{
    this->background = ":/prefix1/images/Bg3";

    scrollArea = new QScrollArea();
    backButton = new QPushButton("Back");
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scrollArea->setFixedSize(ScreenSize::getWidth()*5/6, ScreenSize::getHeigth() - 150);
    backButton->setFixedSize(100, 40);

    areaLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();
    VLayout = new QVBoxLayout(this);
    this->setLayout(VLayout);

    areaLayout->addStretch(1);
    areaLayout->addWidget(scrollArea);
    areaLayout->addStretch(1);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch(1);
    VLayout->addLayout(areaLayout);
    VLayout->addStretch(1);
    VLayout->addLayout(buttonLayout);
    VLayout->addStretch(2);

    connect(backButton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack(pageEnum::MAINMENU);
    });
    connect(scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, [this](int value){
        if (value == scrollArea->verticalScrollBar()->maximum()) {
            loadList();
        }
    });

    backButton->setStyleSheet(
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
        "}"
        );
    scrollArea->setStyleSheet(
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
        "}"
        );
}

void AZListPage::refresh()
{
    refreshList();
}

void AZListPage::refreshList()
{
    if (listWidget){
        scrollArea->takeWidget();
        delete listWidget;
        listWidget = nullptr;
    }

    listLayout = new QVBoxLayout;
    listWidget = new QWidget;
    listWidget->setAutoFillBackground(false);
    listWidget->setStyleSheet("background-color: transparent;");
    listLayout->setSpacing(20);

    it = Word::allWords.begin();
    loadList();
    listWidget->setLayout(listLayout);
    scrollArea->setWidget(listWidget);
}

void AZListPage::loadList()
{
    int count = 0;
    while(count < 30 && it != Word::allWords.end()){
        int rowCount = 0;

        QString letter = it->second->getTerm()[0].toUpper();
        QLabel* label = new QLabel(letter);
        label->setStyleSheet("QLabel {"
                             "   background-color: #e6b800;"
                             "   color: #1c3346;"
                             "   font-size: 18px;"
                             "   font-weight: bold;"
                             "   font-family: 'Trebuchet MS', 'Segoe UI';"
                             "   border-radius: 8px;"
                             "   padding: 4px 10px;"
                             "}");

        QVBoxLayout* BVLayout = new QVBoxLayout;
        QHBoxLayout* letterLayout = new QHBoxLayout;
        BVLayout->setSpacing(12);

        int i = 0;
        QHBoxLayout* buttonsLayout = new QHBoxLayout;
        buttonsLayout->setSpacing(8);

        while(it != Word::allWords.end() && it->second->getTerm()[0].toUpper() == letter){
            QString term = it->second->getTerm();
            QPushButton* wordButton = new QPushButton(term);
            wordButton->setFixedSize(scrollArea->width()/5, 40);
            connect(wordButton, &QPushButton::clicked, this, [term](){
                auto found = Word::allWords.find(term);
                if (found == Word::allWords.end()){
                    return;
                }

                WordPage::entryWord = found->second.get();
                MainWindow::changeStack(pageEnum::WORDPAGE);
            });
            wordButton->setStyleSheet("QPushButton {"
                                      "   background-color: #f5ecd7;"
                                      "   color: #1c3346;"
                                      "   font-size: 15px;"
                                      "   font-weight: bold;"
                                      "   font-family: 'Trebuchet MS', 'Segoe UI';"
                                      "   border-radius: 8px;"
                                      "   padding: 4px 10px;"
                                      "   border: none;"
                                      "}"
                                      "QPushButton:hover {"
                                      "   background-color: #ffffff;"
                                      "}"
                                      "QPushButton:pressed {"
                                      "   background-color: #e0d4b0;"
                                      "}");

            buttonsLayout->addWidget(wordButton);
            ++i;

            if (i == 4){
                buttonsLayout->addStretch(1);
                BVLayout->addLayout(buttonsLayout);
                rowCount++;
                buttonsLayout = new QHBoxLayout;
                buttonsLayout->setSpacing(8);
                i = 0;
            }

            count++;
            ++it;
        }

        if (i > 0){
            buttonsLayout->addStretch(1);
            BVLayout->addLayout(buttonsLayout);
            rowCount++;
        }

        label->setFixedSize(40, rowCount*40 + (rowCount-1)*12);
        letterLayout->addWidget(label);
        letterLayout->addSpacing(12);
        letterLayout->addLayout(BVLayout);
        letterLayout->addStretch(1);

        listLayout->addLayout(letterLayout);
        listLayout->addSpacing(16);
    }
    listLayout->addStretch(1);
}

AZListPage::~AZListPage()
{

}
