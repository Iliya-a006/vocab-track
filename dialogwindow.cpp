#include "dialogwindow.h"
#include "ui_dialogwindow.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>

DialogWindow::DialogWindow(QString text, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Warning");
    this->setFixedSize(300, 150);

    setStyleSheet(
        "QDialog {"
        "   background-color: #1c3346;"
        "}"
        "QLabel {"
        "   color: #cfe3ee;"
        "}"
        "QPushButton {"
        "   background-color: #274a63;"
        "   color: #cfe3ee;"
        "   border-radius: 4px;"
        "   padding: 6px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #5aa9d6;"
        "}"
        "QLineEdit {"
        "   background-color: #274a63;"
        "   color: #cfe3ee;"
        "   border: 1px solid #5aa9d6;"
        "   border-radius: 3px;"
        "}"
        );


    QPushButton *okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
    QPushButton *cancelBtn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    QLabel* label = new QLabel(text, this);

    okBtn->setFixedSize(70, 30);
    cancelBtn->setFixedSize(70, 30);
    label->setFixedSize(270, 40);

    label->setStyleSheet(
        "QLabel {"
        "   background: transparent;"
        "   font-size: 13px;"
        "   font-weight: bold;"
        "   padding: 4px;"
        "}"
        );


    QVBoxLayout* vLayout = new QVBoxLayout;
    QHBoxLayout* labelLayout = new QHBoxLayout;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;

    labelLayout->addWidget(label);
    buttonsLayout->addStretch(5);
    buttonsLayout->addWidget(okBtn);
    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addStretch(1);

    vLayout->addStretch(1);
    vLayout->addLayout(labelLayout);
    vLayout->addStretch(3);
    vLayout->addLayout(buttonsLayout);
    vLayout->addStretch(1);

    this->setLayout(vLayout);


}

DialogWindow::~DialogWindow()
{
    delete ui;
}
