#ifndef DLISTPAGE_H
#define DLISTPAGE_H

#include "page.h"
#include <QWidget>

class DListPage : public Page
{
    Q_OBJECT

public:
    explicit DListPage(QWidget *parent = nullptr);
    ~DListPage();

    void refresh() override;
};

#endif // DLISTPAGE_H
