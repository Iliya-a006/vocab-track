#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QDialog>

namespace Ui {
class DialogWindow;
}

class DialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWindow(QString text, QWidget *parent = nullptr);
    ~DialogWindow();

private:
    Ui::DialogWindow *ui;
};

#endif // DIALOGWINDOW_H
