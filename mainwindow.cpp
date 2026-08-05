#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainmenu.h"
#include "word.h"
#include <QStackedWidget>
#include <QPainter>
#include "page.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    Word::loadWords();

    MainMenu* main_menu = new MainMenu(m_stack);
    m_stack->addWidget(main_menu);
    changeStack(pageEnum::MAINMENU);
}

QStackedWidget* MainWindow::m_stack;
void MainWindow::changeStack(int index)
{
    MainWindow::m_stack->setCurrentIndex(index);
    m_stack->update();

    QWidget* widget = m_stack->currentWidget();
    Page* page = qobject_cast<Page*>(widget);
    page->refresh();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QWidget *widget = m_stack->currentWidget();
    Page *page = qobject_cast<Page*>(widget);
    QPixmap bg(page->background);
    if (!bg.isNull()) {
        painter.drawPixmap(rect(), bg.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
    QWidget::paintEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}








