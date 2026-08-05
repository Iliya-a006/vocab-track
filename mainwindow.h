#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstackedwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


enum pageEnum{
    MAINMENU
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    static QStackedWidget* m_stack;
    static void changeStack(int index);

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *event) override;
};
#endif // MAINWINDOW_H
