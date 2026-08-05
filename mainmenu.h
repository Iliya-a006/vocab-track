#ifndef MAINMENU_H
#define MAINMENU_H

#include "page.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <qboxlayout.h>

class MainMenu : public Page
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    void refresh() override;

private:
    QPushButton* TRbutton;
    QPushButton* ADDbutton;
    QPushButton* A_Zbutton;
    QPushButton* LBDbutton;
    QPushButton* SEARCHbutton;

    QVBoxLayout* Vlayout;
    QHBoxLayout* Hlayout;
};

#endif // MAINMENU_H
