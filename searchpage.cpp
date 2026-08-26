#include "searchpage.h"
#include "screensize.h"
#include "wordpage.h"
#include "mainwindow.h"

SearchPage::SearchPage(QWidget *parent)
    : Page(parent)
{
    this->background = ":/prefix1/images/Bg2";

    topLabel = new QLabel("SEARCH A WORD");
    searchEdit = new QLineEdit();
    searchButton = new QPushButton("Search");
    scrollArea = new QScrollArea(this);
    backButton = new QPushButton("Back");
    outterLayout = new QVBoxLayout(this);
    listWidget = new QWidget();
    listLayout = new QVBoxLayout();
    listWidget->setLayout(listLayout);
    scrollArea->setWidget(listWidget);
    scrollArea->setWidgetResizable(true);
    listWidget->setAutoFillBackground(false);
    listWidget->setStyleSheet("background-color: transparent;");

    topLabel->setFixedSize(240, 50);
    searchEdit->setFixedSize(ScreenSize::getWidth()*3/4, 40);
    searchButton->setFixedSize(120, 40);
    backButton->setFixedSize(80, 40);
    scrollArea->setFixedWidth(searchEdit->width() + searchButton->width());
    scrollArea->setFixedHeight(0);

    QHBoxLayout* topLayout = new QHBoxLayout;
    QHBoxLayout* searchBarLayout = new QHBoxLayout;
    QHBoxLayout* backBLayout = new QHBoxLayout;

    topLayout->addStretch(1);
    topLayout->addWidget(topLabel);
    topLayout->addStretch(1);

    searchBarLayout->addStretch(1);
    searchBarLayout->addWidget(searchEdit);
    searchBarLayout->addWidget(searchButton);
    searchBarLayout->addStretch(1);

    backBLayout->addStretch(1);
    backBLayout->addWidget(backButton);
    backBLayout->addStretch(1);

    outterLayout->addStretch(1);
    outterLayout->addLayout(topLayout);
    outterLayout->addLayout(searchBarLayout);
    outterLayout->addStretch(12);
    outterLayout->addLayout(backBLayout);
    outterLayout->addStretch(2);


    connect(searchButton, &QPushButton::clicked, this, [this](){
        refreshResults();
    });
    connect(backButton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack(pageEnum::MAINMENU);
    });
    connect(searchEdit, &QLineEdit::returnPressed, searchButton, &QPushButton::click);


    topLabel->setStyleSheet(
        "QLabel {"
        "   background-color: #1c3346;"
        "   color: white;"
        "   font-size: 26px;"
        "   font-weight: bold;"
        "   font-family: 'Trebuchet MS', 'Segoe UI';"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 10px;"
        "   padding: 6px 16px;"
        "}"
        );
    searchEdit->setStyleSheet(        "QLineEdit {"
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
                              "}");
    searchButton->setStyleSheet(        "QPushButton {"
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
                                "}");
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
    backButton->setStyleSheet(        "QPushButton {"
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
                              "}");

    setupWarningLabel();
}

void SearchPage::refresh()
{
    scrollArea->move(searchEdit->x(), searchEdit->y() + searchEdit->height() + 10);
    maxListHeigth = backButton->y() - searchEdit->y() - 80;

    if (MainWindow::prevPage != pageEnum::WORDPAGE){
        clearResults();
        words.clear();
        searchEdit->setText("");
        scrollArea->setFixedHeight(0);
    }
}

void SearchPage::refreshResults()
{
    clearResults();
    words.clear();

    if (!searchEdit->text().length()){
        return;
    }

    for (const auto& [key, w] : Word::allWords)
    {
        if (w->getTerm().contains(searchEdit->text(), Qt::CaseInsensitive))
        {
            words.push_back(w.get());
        }
    }

    if (!words.size()){
        showWarning("No matching word found!", 3000);
        scrollArea->setFixedHeight(0);
        return;
    }

    int heigth = words.size() * 60;
    if (heigth > maxListHeigth){
        scrollArea->setFixedHeight(maxListHeigth);
    } else {
        scrollArea->setFixedHeight(heigth);
    }

    for (auto w : words){
        QString term = w->getTerm();
        QPushButton*  wordButton = new QPushButton(term);
        wordButton->setFixedSize(scrollArea->width()-40, 40);
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

        connect(wordButton, &QPushButton::clicked, this, [term](){
            auto found = Word::allWords.find(term);
            if (found == Word::allWords.end()){
                return;
            }
            WordPage::entryWord = found->second.get();
            MainWindow::changeStack(pageEnum::WORDPAGE);
        });
        listLayout->addWidget(wordButton);
    }
    listLayout->addStretch();
}

void SearchPage::clearResults()
{
    QLayoutItem* item;
    while ((item = listLayout->takeAt(0)) != nullptr)
    {
        if (QWidget* w = item->widget())
            delete w;
        delete item;
    }
}

SearchPage::~SearchPage()
{
}







