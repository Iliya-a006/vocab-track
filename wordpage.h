#ifndef WORDPAGE_H
#define WORDPAGE_H

#include <QWidget>
#include "page.h"

class WordPage : public Page
{
    Q_OBJECT

public:
    explicit WordPage(QWidget *parent = nullptr);
    ~WordPage();

    void refresh() override;
};

#endif // WORDPAGE_H
