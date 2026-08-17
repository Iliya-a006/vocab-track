#ifndef AZLISTPAGE_H
#define AZLISTPAGE_H

#include "page.h"
#include <QWidget>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qscrollarea.h>

class AZListPage : public Page
{
    Q_OBJECT

public:
    explicit AZListPage(QWidget *parent = nullptr);
    ~AZListPage();

    void refresh() override;

private:
    QScrollArea* scrollArea;
    QVector<QPushButton*> allOptions;
    QVector<QLabel*> Labels;
    QPushButton* backButton;

    QHBoxLayout* areaLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* VLayout;
};

#endif // AZLISTPAGE_H






