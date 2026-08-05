#ifndef MAINMENU_H
#define MAINMENU_H

#include "page.h"
#include <QWidget>

class MainMenu : public Page
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    void refresh() override;
};

#endif // MAINMENU_H
