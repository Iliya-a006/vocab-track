#include "searchpage.h"
#include "screensize.h"

SearchPage::SearchPage(QWidget *parent)
    : Page(parent)
{
    this->background = ":/prefix1/images/Bg2";

    topLabel = new QLabel("SEARCH A WORD", this);
    searchEdit = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    backButton = new QPushButton("Back", this);
    outterLayout = new QVBoxLayout(this);

    topLabel->setFixedSize(240, 50);
    searchEdit->setFixedSize(ScreenSize::getWidth()*3/4, 40);
    searchButton->setFixedSize(120, 40);
    backButton->setFixedSize(80, 40);

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
}

void SearchPage::refresh()
{

}

void SearchPage::refreshResults()
{

}

SearchPage::~SearchPage()
{
}
