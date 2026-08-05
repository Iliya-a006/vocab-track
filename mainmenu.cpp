#include "mainmenu.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mainwindow.h"

MainMenu::MainMenu(QWidget *parent)
    : Page(parent)
{
    this->background = ":/prefix1/images/Bg2";

    TRbutton = new QPushButton("Today's Review", this);
    ADDbutton = new QPushButton("Add New Word", this);
    A_Zbutton = new QPushButton("A_Z List", this);
    LBDbutton = new QPushButton("List By Difficulty", this);
    SEARCHbutton = new QPushButton("Search", this);

    TRbutton->setFixedSize(200, 60);
    ADDbutton->setFixedSize(200, 60);
    A_Zbutton->setFixedSize(200, 60);
    LBDbutton->setFixedSize(200, 60);
    SEARCHbutton->setFixedSize(200, 60);

    TRbutton->setStyleSheet("QPushButton {"
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
                            "}");
    A_Zbutton->setStyleSheet(TRbutton->styleSheet());
    ADDbutton->setStyleSheet(TRbutton->styleSheet());
    LBDbutton->setStyleSheet(TRbutton->styleSheet());
    SEARCHbutton->setStyleSheet(TRbutton->styleSheet());


    Vlayout = new QVBoxLayout();
    Vlayout->addStretch(4);
    Vlayout->addWidget(TRbutton);
    Vlayout->addStretch(1);
    Vlayout->addWidget(ADDbutton);
    Vlayout->addStretch(1);
    Vlayout->addWidget(A_Zbutton);
    Vlayout->addStretch(1);
    Vlayout->addWidget(LBDbutton);
    Vlayout->addStretch(1);
    Vlayout->addWidget(SEARCHbutton);
    Vlayout->addStretch(4);

    Hlayout = new QHBoxLayout();
    Hlayout->addStretch();
    Hlayout->addLayout(Vlayout);
    Hlayout->addStretch();
    this->setLayout(Hlayout);


    connect(TRbutton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack(pageEnum::TODAYLIST);
    });
    connect(ADDbutton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack(pageEnum::ADDPAGE);
    });
    connect(A_Zbutton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack(pageEnum::AZLIST);
    });
    connect(LBDbutton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack(pageEnum::DLIST);
    });
    connect(SEARCHbutton, &QPushButton::clicked, this, [](){
        MainWindow::changeStack(pageEnum::SEARCHPAGE);
    });
}

void MainMenu::refresh()
{

}

MainMenu::~MainMenu()
{

}
