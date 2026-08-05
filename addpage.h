#ifndef ADDPAGE_H
#define ADDPAGE_H

#include "page.h"
#include <QWidget>

class AddPage : public Page
{
    Q_OBJECT

public:
    explicit AddPage(QWidget *parent = nullptr);
    ~AddPage();

    void refresh() override;

};

#endif // ADDPAGE_H
