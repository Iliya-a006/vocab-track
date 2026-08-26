#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstackedwidget.h>
#include "mainmenu.h"
#include "todaypage.h"
#include "addpage.h"
#include "azlistpage.h"
#include "difficultylistpage.h"
#include "searchpage.h"
#include "wordpage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


enum pageEnum{
    MAINMENU,
    TODAYLIST,
    ADDPAGE,
    AZLIST,
    DLIST,
    SEARCHPAGE,
    WORDPAGE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    static QStackedWidget* m_stack;
    static void changeStack(int index);
    static int prevPage;

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *event) override;
    void loadPages();

    std::unique_ptr<MainMenu> main_menu;
    std::unique_ptr<TodayPage> today_page;
    std::unique_ptr<AddPage> add_page;
    std::unique_ptr<AZListPage> az_list;
    std::unique_ptr<DifficultyListPage> dlist_page;
    std::unique_ptr<SearchPage> search_page;
    std::unique_ptr<WordPage> word_page;
};
#endif // MAINWINDOW_H











