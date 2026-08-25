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

    loadPages();
    changeStack(pageEnum::MAINMENU);
}

QStackedWidget* MainWindow::m_stack;
int MainWindow::prevPage = pageEnum::MAINMENU;
void MainWindow::changeStack(int index)
{
    prevPage = m_stack->currentIndex();

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

void MainWindow::loadPages()
{
    main_menu = std::make_unique<MainMenu>();
    today_page = std::make_unique<TodayPage>();
    add_page = std::make_unique<AddPage>();
    az_list = std::make_unique<AZListPage>();
    dlist_page = std::make_unique<DListPage>();
    search_page = std::make_unique<SearchPage>();
    word_page = std::make_unique<WordPage>();

    m_stack->addWidget(main_menu.get());
    m_stack->addWidget(today_page.get());
    m_stack->addWidget(add_page.get());
    m_stack->addWidget(az_list.get());
    m_stack->addWidget(dlist_page.get());
    m_stack->addWidget(search_page.get());
    m_stack->addWidget(word_page.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}








