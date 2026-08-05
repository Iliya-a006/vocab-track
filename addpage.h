#ifndef ADDPAGE_H
#define ADDPAGE_H

#include "page.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

class AddPage : public Page
{
    Q_OBJECT

public:
    explicit AddPage(QWidget *parent = nullptr);
    ~AddPage();

    void refresh() override;

private:
    QLabel* termLabel;
    QLabel* POSLabel;
    QLabel* exampleLabel;
    QLabel* synonymLabel;
    QLabel* translationLabel;

    QLineEdit* termEdit;
    QLineEdit* exampleEdit;
    QLineEdit* synonymEdit;
    QLineEdit* translationEdit;
    QComboBox* POSEdit;

    QPushButton* backButton;
    QPushButton* saveButton;
    QPushButton* synonymSave;
    QPushButton* translationSave;

    QVBoxLayout* VLayout;
    QHBoxLayout* row1LabelsLayout;
    QHBoxLayout* row1EditsLayout;
    QHBoxLayout* row2LabelsLayout;
    QHBoxLayout* row2EditsLayout;
    QHBoxLayout* row3LabelsLayout;
    QHBoxLayout* row3EditsLayout;
    QHBoxLayout* HbuttonsLayout;

    void layoutLoad();
    void widgetsLoad();
};

#endif // ADDPAGE_H






