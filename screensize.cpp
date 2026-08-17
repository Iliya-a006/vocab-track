#include "screensize.h"
#include <QGuiApplication>
#include <qscreen.h>

ScreenSize::ScreenSize()
{

}

int* ScreenSize::width = nullptr;
int* ScreenSize::heigth = nullptr;
QSize* ScreenSize::size = nullptr;

int ScreenSize::getWidth()
{
    if (!width){
        QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
        width = new int;
        *width = screenGeometry.width();
    }
    return *width;
}

int ScreenSize::getHeigth()
{
    if (!heigth){
        QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
        heigth = new int;
        *heigth = screenGeometry.height();
    }
    return *heigth;
}

QSize ScreenSize::getSize()
{
    if (!size){
        QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
        size = new QSize;
        *size = screenGeometry.size();
    }
    return *size;
}