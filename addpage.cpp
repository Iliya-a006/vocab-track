#include "addpage.h"

AddPage::AddPage(QWidget *parent)
    : Page(parent)
{
    this->background = ":/prefix1/images/Bg2";

    widgetsLoad();
    layoutLoad();
}

void AddPage::refresh()
{

}

void AddPage::layoutLoad()
{
    VLayout = new QVBoxLayout(this);
    row1LabelsLayout = new QHBoxLayout;
    row1EditsLayout = new QHBoxLayout;
    row2LabelsLayout = new QHBoxLayout;
    row2EditsLayout = new QHBoxLayout;
    row3LabelsLayout = new QHBoxLayout;
    row3EditsLayout = new QHBoxLayout;
    HbuttonsLayout = new QHBoxLayout;

    row1LabelsLayout->addStretch();
    row1LabelsLayout->addWidget(termLabel);
    row1LabelsLayout->addStretch();

    row1EditsLayout->addStretch();
    row1EditsLayout->addWidget(termEdit);
    row1EditsLayout->addStretch();

    row2LabelsLayout->addStretch();
    row2LabelsLayout->addWidget(POSLabel);
    row2LabelsLayout->addStretch();
    row2LabelsLayout->addWidget(exampleLabel);
    row2LabelsLayout->addStretch();

    row2EditsLayout->addStretch();
    row2EditsLayout->addWidget(POSEdit);
    row2EditsLayout->addStretch();
    row2EditsLayout->addWidget(exampleEdit);
    row2EditsLayout->addStretch();

    row3LabelsLayout->addStretch();
    row3LabelsLayout->addWidget(synonymLabel);
    row3LabelsLayout->addStretch();
    row3LabelsLayout->addWidget(translationLabel);
    row3LabelsLayout->addStretch();

    row3EditsLayout->addStretch();
    row3EditsLayout->addWidget(synonymEdit);
    row3EditsLayout->addWidget(synonymSave);
    row3EditsLayout->addStretch();
    row3EditsLayout->addWidget(translationEdit);
    row3EditsLayout->addWidget(translationSave);
    row3EditsLayout->addStretch();

    HbuttonsLayout->addStretch(1);
    HbuttonsLayout->addWidget(backButton);
    HbuttonsLayout->addStretch(8);
    HbuttonsLayout->addWidget(saveButton);
    HbuttonsLayout->addStretch(1);

    VLayout->addStretch(1);
    VLayout->addLayout(row1LabelsLayout);
    VLayout->addLayout(row1EditsLayout);
    VLayout->addStretch(1);
    VLayout->addLayout(row2LabelsLayout);
    VLayout->addLayout(row2EditsLayout);
    VLayout->addStretch(1);
    VLayout->addLayout(row3LabelsLayout);
    VLayout->addLayout(row3EditsLayout);
    VLayout->addStretch(2);
    VLayout->addLayout(HbuttonsLayout);
    VLayout->addStretch(1);
}

void AddPage::widgetsLoad()
{
    termLabel        = new QLabel("Enter A New Word", this);
    POSLabel         = new QLabel("Part Of Speech", this);
    exampleLabel     = new QLabel("Example", this);
    synonymLabel     = new QLabel("Add Synonym", this);
    translationLabel = new QLabel("Add Translation", this);

    termEdit        = new QLineEdit(this);
    exampleEdit     = new QLineEdit(this);
    synonymEdit     = new QLineEdit(this);
    translationEdit = new QLineEdit(this);

    POSEdit = new QComboBox(this);
    POSEdit->addItem("Noun");
    POSEdit->addItem("Verbe");
    POSEdit->addItem("Adjective");
    POSEdit->addItem("Adverbe");
    POSEdit->setCurrentIndex(-1);

    backButton      = new QPushButton("Back", this);
    saveButton      = new QPushButton("Save", this);
    synonymSave     = new QPushButton("Save", this);
    translationSave = new QPushButton("Save", this);


    termLabel->setFixedSize(160, 26);
    POSLabel->setFixedSize(120, 26);
    exampleLabel->setFixedSize(120, 26);
    synonymLabel->setFixedSize(120, 26);
    translationLabel->setFixedSize(120, 26);

    termEdit->setFixedSize(240, 34);
    exampleEdit->setFixedSize(240, 34);
    synonymEdit->setFixedSize(180, 34);
    translationEdit->setFixedSize(180, 34);

    POSEdit->setFixedSize(240, 34);

    backButton->setFixedSize(120, 40);
    saveButton->setFixedSize(120, 40);
    synonymSave->setFixedSize(90, 34);
    translationSave->setFixedSize(90, 34);


    QString fieldLabelStyle =
        "QLabel {"
        "   background-color: transparent;"
        "   color: #9fb8c9;"
        "   font-size: 14px;"
        "   font-family: 'Trebuchet MS', 'Segoe UI';"
        "}";
    termLabel->setStyleSheet("QLabel {"
                             "   background-color: transparent;"
                             "   color: white;"
                             "   font-size: 18px;"
                             "   font-family: 'Trebuchet MS', 'Segoe UI';"
                             "}");
    POSLabel->setStyleSheet(fieldLabelStyle);
    exampleLabel->setStyleSheet(fieldLabelStyle);
    synonymLabel->setStyleSheet(fieldLabelStyle);
    translationLabel->setStyleSheet(fieldLabelStyle);


    QString lineEditStyle =
        "QLineEdit {"
        "   background-color: #1c3346;"
        "   color: #eaf4fb;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 8px;"
        "   padding: 4px 10px;"
        "   font-size: 14px;"
        "   font-family: 'Trebuchet MS', 'Segoe UI';"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #cfe3ee;"
        "}";
    termEdit->setStyleSheet(lineEditStyle);
    exampleEdit->setStyleSheet(lineEditStyle);
    synonymEdit->setStyleSheet(lineEditStyle);
    translationEdit->setStyleSheet(lineEditStyle);


    POSEdit->setStyleSheet(
        "QComboBox {"
        "   background-color: #1c3346;"
        "   color: #eaf4fb;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 8px;"
        "   padding: 4px 10px;"
        "   font-size: 14px;"
        "   font-family: 'Trebuchet MS', 'Segoe UI';"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #1c3346;"
        "   color: #eaf4fb;"
        "   selection-background-color: #5aa9d6;"
        "}"
        );


    saveButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #5aa9d6;"
        "   color: #0f1c26;"
        "   border: 2px solid #cfe3ee;"
        "   border-radius: 10px;"
        "   padding: 8px 20px;"
        "   font-size: 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #6fbce8;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #3f7094;"
        "}"
        );


    backButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #274a63;"
        "   color: #eaf4fb;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 10px;"
        "   padding: 8px 20px;"
        "   font-size: 15px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #3f7094;"
        "   border: 2px solid #cfe3ee;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #16232f;"
        "}"
        );


    QString smallAddButtonStyle =
        "QPushButton {"
        "   background-color: #274a63;"
        "   color: #eaf4fb;"
        "   border: 2px solid #5aa9d6;"
        "   border-radius: 8px;"
        "   padding: 4px 10px;"
        "   font-size: 13px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #3f7094;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #16232f;"
        "}";
    synonymSave->setStyleSheet(smallAddButtonStyle);
    translationSave->setStyleSheet(smallAddButtonStyle);
}

AddPage::~AddPage()
{
}
