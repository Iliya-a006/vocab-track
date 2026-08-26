#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <qlabel.h>

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
    QLabel* warningLabel;

    void setupWarningLabel();
    void showWarning(QString text, int time);

public:
    virtual void refresh() = 0;
};

#endif // PAGE_H
