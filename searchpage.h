#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include "page.h"
#include <QWidget>

class SearchPage : public Page
{
    Q_OBJECT

public:
    explicit SearchPage(QWidget *parent = nullptr);
    ~SearchPage();

    void refresh() override;

};

#endif // SEARCHPAGE_H
