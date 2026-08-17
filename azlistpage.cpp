#include "azlistpage.h"
#include "screensize.h"

AZListPage::AZListPage(QWidget *parent)
    : Page(parent)
{
    this->background = ":/prefix1/images/Bg3";

    scrollArea = new QScrollArea();
    backButton = new QPushButton("Back");

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

}

AZListPage::~AZListPage()
{

}
