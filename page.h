#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = nullptr);
    virtual ~Page();
    friend class MainWindow;

protected:
    QString background;
    int stackIndex;

public:
    virtual void refresh() = 0;
};

#endif // PAGE_H
