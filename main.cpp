#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("VocabTrack");
    Word::loadWords();
    Word::resetDailyReviewStatusIfNeeded();
    MainWindow w;
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    w.setFixedSize(screenGeometry.size());
    w.move(screenGeometry.topLeft());
    w.show();
    return QApplication::exec();
}
