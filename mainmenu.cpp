#include "mainmenu.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget *parent)
    : Page(parent)
{
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


    Vlayout = new QVBoxLayout();
    Vlayout->addStretch();
    Vlayout->addStretch();
    Vlayout->addStretch();
    Vlayout->addStretch();
    Vlayout->addWidget(TRbutton);
    Vlayout->addStretch();
    Vlayout->addWidget(ADDbutton);
    Vlayout->addStretch();
    Vlayout->addWidget(A_Zbutton);
    Vlayout->addStretch();
    Vlayout->addWidget(LBDbutton);
    Vlayout->addStretch();
    Vlayout->addWidget(SEARCHbutton);
    Vlayout->addStretch();
    Vlayout->addStretch();
    Vlayout->addStretch();
    Vlayout->addStretch();

    Hlayout = new QHBoxLayout();
    Hlayout->addStretch();
    Hlayout->addLayout(Vlayout);
    Hlayout->addStretch();
    this->setLayout(Hlayout);
}

void MainMenu::refresh()
{

}

MainMenu::~MainMenu()
{

}
