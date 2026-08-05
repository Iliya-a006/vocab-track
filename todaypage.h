#ifndef TODAYPAGE_H
#define TODAYPAGE_H

#include "page.h"
#include <QWidget>

class TodayPage : public Page
{
    Q_OBJECT

public:
    explicit TodayPage(QWidget *parent = nullptr);
    ~TodayPage();

    void refresh() override;

};

#endif // TODAYPAGE_H
