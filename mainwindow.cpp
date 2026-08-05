#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "word.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Word::loadWords();
}

MainWindow::~MainWindow()
{
    delete ui;
}








