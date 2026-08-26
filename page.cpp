#include "page.h"
#include <qtimer.h>

Page::Page(QWidget *parent)
    : QWidget(parent)
{

}

void Page::setupWarningLabel()
{
    warningLabel = new QLabel(this);
    warningLabel->setFixedHeight(40);
    warningLabel->move(70, 50);
    warningLabel->setStyleSheet(
        "QLabel {"
        "   color: #ffffff;"
        "   background-color: #d32f2f;"
        "   border-radius: 6px;"
        "   padding: 8px 12px;"
        "   font-weight: bold;"
        "   font-size: 15px;"
        "}"
        );
    warningLabel->hide();
}

void Page::showWarning(QString text, int time)
{
    warningLabel->setText(text);
    QFontMetrics fm(warningLabel->font());
    warningLabel->setFixedWidth(fm.horizontalAdvance(warningLabel->text()) + 80);
    warningLabel->show();
    QTimer::singleShot(time, this, [this](){
        warningLabel->hide();
    });
}

Page::~Page()
{

}
