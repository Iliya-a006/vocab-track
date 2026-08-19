#ifndef AZLISTPAGE_H
#define AZLISTPAGE_H

#include "page.h"
#include "word.h"
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
    void refreshList();
    void loadList();

    QScrollArea* scrollArea;
    QVector<QPushButton*> allOptions;
    QVector<QLabel*> Labels;
    QPushButton* backButton;

    QHBoxLayout* areaLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* VLayout;

    QVBoxLayout* listLayout;
    QWidget* listWidget;
    QVector<QHBoxLayout*> listHLayouts;

    int countWords;
    std::map<QString, std::unique_ptr<Word>, CaseInsensitiveLess>::iterator it;
};

#endif // AZLISTPAGE_H






