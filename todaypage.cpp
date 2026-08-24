#include "todaypage.h"
#include "word.h"
#include "mainwindow.h"
#include "wordpage.h"

TodayPage::TodayPage(QWidget *parent)
    : Page(parent)
{
    this->background = ":/prefix1/images/Bg1";
    setupUI();
}

void TodayPage::refresh()
{
    WordPage::index = 0;

    updateList();
}

void TodayPage::setupUI()
{
    startButton = new QPushButton("Start", this);
    backButton = new QPushButton("Back", this);
    topLabel = new QLabel("Today's Words", this);
    scrollArea = new QScrollArea(this);

    connect(backButton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack(pageEnum::MAINMENU);
    });
    connect(startButton, &QPushButton::clicked, this, [this](){
        if (!remainingWords.size()){
            return;
        }
        MainWindow::changeStack(pageEnum::WORDPAGE);
    });

    startButton->setFixedSize(120, 44);
    backButton->setFixedSize(120, 44);
    topLabel->setFixedSize(340, 70);

    scrollArea->setFixedWidth(1000);
    scrollArea->setMinimumHeight(400);
    scrollArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    scrollArea->setWidgetResizable(true);

    topLabel->setAlignment(Qt::AlignCenter);
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

    startButton->setStyleSheet(
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
        "}"
        );

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

    QHBoxLayout* topLayout = new QHBoxLayout();
    QHBoxLayout* listLayout = new QHBoxLayout();
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    topLayout->addWidget(topLabel);

    listLayout->addWidget(scrollArea);

    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(backButton);
    buttonsLayout->addStretch(4);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addStretch(1);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addStretch(1);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(listLayout, 1);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addStretch(2);
    this->setLayout(mainLayout);
}

void TodayPage::updateList()
{
    QWidget* scrollWidget = new QWidget;
    scrollWidget->setAutoFillBackground(false);
    scrollWidget->setStyleSheet("background-color: transparent;");
    scrollWidget->setLayout(setupList());

    scrollArea->setWidget(scrollWidget);
}

QVBoxLayout* TodayPage::setupList()
{
    reviewedWords.clear();
    remainingWords.clear();

    for (const auto& [key, w] : Word::allWords) {
        bool dueToday = w->getNextDate() <= QDate::currentDate();
        bool reviewedToday = w->getReviewed().first;

        if (dueToday || reviewedToday) {
            if (reviewedToday)
                reviewedWords.push_back(w.get());
            else
                remainingWords.push_back(w.get());
        }
    }

    QVector<Word*> allTodayWords;
    allTodayWords.reserve(reviewedWords.size() + remainingWords.size());
    for (auto w : reviewedWords) allTodayWords.push_back(w);
    for (auto w : remainingWords) allTodayWords.push_back(w);

    QVBoxLayout* listLayout = new QVBoxLayout();
    listLayout->setSpacing(12);
    listLayout->setContentsMargins(10, 10, 10, 10);

    const int itemsPerRow = 4;
    QHBoxLayout* rowLayout = nullptr;
    int count = 0;

    for (auto w : allTodayWords) {
        if (count % itemsPerRow == 0) {
            if (rowLayout)
                listLayout->addLayout(rowLayout);
            rowLayout = new QHBoxLayout();
            rowLayout->setSpacing(10);
            count = 0;
        }

        QLabel* label = new QLabel(w->getTerm());
        label->setFixedSize(180, 40);
        label->setStyleSheet("QLabel {"
                             "   background-color: #f5ecd7;"
                             "   color: #1c3346;"
                             "   font-size: 15px;"
                             "   font-weight: bold;"
                             "   font-family: 'Trebuchet MS', 'Segoe UI';"
                             "   border-radius: 8px;"
                             "   padding: 4px 10px;"
                             "}");
        rowLayout->addWidget(label);

        QLabel* tickLabel = new QLabel();
        tickLabel->setFixedSize(40, 40);
        if (w->getReviewed().first) {
            if (w->getReviewed().second) {
                tickLabel->setText("✓");
                tickLabel->setStyleSheet("QLabel {"
                                         "   background-color: transparent;"
                                         "   color: #2ecc71;"
                                         "   font-size: 20px;"
                                         "   font-weight: bold;"
                                         "}");
            } else {
                tickLabel->setText("✗");
                tickLabel->setStyleSheet("QLabel {"
                                         "   background-color: transparent;"
                                         "   color: #e74c3c;"
                                         "   font-size: 20px;"
                                         "   font-weight: bold;"
                                         "}");
            }
        } else {
            tickLabel->setText("");
        }
        rowLayout->addWidget(tickLabel);

        ++count;
    }

    if (rowLayout) {
        if (count < itemsPerRow)
            rowLayout->addStretch(1);
        listLayout->addLayout(rowLayout);
    }
    listLayout->addStretch(1);

    return listLayout;
}

TodayPage::~TodayPage()
{

}