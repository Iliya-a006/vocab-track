#include "difficultylistpage.h"
#include "mainwindow.h"
#include "screensize.h"
#include "word.h"
#include "wordpage.h"
#include <QScrollBar>
#include <algorithm>

DifficultyListPage::DifficultyListPage(QWidget *parent)
    : Page(parent)
    , listWidget(nullptr)
    , loadIndex(0)
{
    this->background = ":/prefix1/images/Bg3";

    scrollArea = new QScrollArea();
    backButton = new QPushButton("Back");
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scrollArea->setFixedSize(ScreenSize::getWidth()*5/6, ScreenSize::getHeigth() - 150);
    backButton->setFixedSize(100, 40);

    sortLabel = new VerticalSortLabel("EASIEST \u2190 HARDEST");
    sortLabel->setFixedSize(44, 260);

    areaLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();
    VLayout = new QVBoxLayout(this);
    this->setLayout(VLayout);

    areaLayout->addStretch(1);
    areaLayout->addWidget(sortLabel, 0, Qt::AlignVCenter);
    areaLayout->addSpacing(10);
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

void DifficultyListPage::refresh()
{
    refreshList();
}

void DifficultyListPage::refreshList()
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

    // Word::allWords is a map ordered alphabetically (CaseInsensitiveLess),
    // so it can't be walked in difficulty order directly.
    // We take a flat snapshot of raw Word* (non-owning, map still owns them)
    // and sort that snapshot by correctReviews ascending -> hardest words first.
    sortedWords.clear();
    sortedWords.reserve(Word::allWords.size());
    for (const auto& [key, val] : Word::allWords){
        sortedWords.push_back(val.get());
    }
    std::stable_sort(sortedWords.begin(), sortedWords.end(),
                     [](Word* a, Word* b){
                         return a->getCorrects() < b->getCorrects();
                     });

    loadIndex = 0;
    loadList();
    listWidget->setLayout(listLayout);
    scrollArea->setWidget(listWidget);
}

void DifficultyListPage::loadList()
{
    // a previous call to loadList() (either from refreshList() or from a
    // scroll-triggered load) always ends with listLayout->addStretch(1).
    // remove that leftover spacer here so it doesn't pile up on every call.
    if (listLayout->count() > 0){
        QLayoutItem* lastItem = listLayout->itemAt(listLayout->count() - 1);
        if (lastItem && lastItem->spacerItem()){
            listLayout->removeItem(lastItem);
            delete lastItem;
        }
    }

    int count = 0;
    int i = 0;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->setSpacing(8);

    while (count < 30 && loadIndex < sortedWords.size()){
        QString term = sortedWords[loadIndex]->getTerm();

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
        ++count;
        ++loadIndex;

        if (i == 4){
            buttonsLayout->addStretch(1);
            listLayout->addLayout(buttonsLayout);
            buttonsLayout = new QHBoxLayout;
            buttonsLayout->setSpacing(8);
            i = 0;
        }
    }

    if (i > 0){
        buttonsLayout->addStretch(1);
        listLayout->addLayout(buttonsLayout);
    } else {
        // last row was already flushed (or nothing was added this call) ->
        // this freshly created layout is unused, delete it to avoid a leak
        delete buttonsLayout;
    }

    listLayout->addStretch(1);
}

DifficultyListPage::~DifficultyListPage()
{

}