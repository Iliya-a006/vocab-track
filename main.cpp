#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    w.setFixedSize(screenGeometry.size());
    w.move(screenGeometry.topLeft());
    w.show();
    return QApplication::exec();
}
