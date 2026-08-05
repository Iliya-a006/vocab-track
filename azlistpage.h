#ifndef AZLISTPAGE_H
#define AZLISTPAGE_H

#include "page.h"
#include <QWidget>

class AZListPage : public Page
{
    Q_OBJECT

public:
    explicit AZListPage(QWidget *parent = nullptr);
    ~AZListPage();

    void refresh() override;
};

#endif // AZLISTPAGE_H
