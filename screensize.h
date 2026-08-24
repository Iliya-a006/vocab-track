#ifndef SCREENSIZE_H
#define SCREENSIZE_H

#include <qsize.h>

class ScreenSize
{
public:
    ScreenSize();

    static int getWidth();
    static int getHeigth();
    static QSize getSize();
private:
    static int* width;
    static int* heigth;
    static QSize* size;
};

#endif // SCREENSIZE_H
