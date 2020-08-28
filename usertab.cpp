#include "usertab.h"

UserTab::UserTab(QWidget *parent) : QWidget(parent)
{
    isDone = false;
    uiInit();

    connect(ui_btnAddGoal, &QPushButton::clicked, this, &UserTab::fncAddGoal);
}


void UserTab::fncAddGoal()
{

    QString inputText = ui_newGoal->toPlainText();
    goals.push_back(inputText);

    //add goal in UI
    QHBoxLayout* layout = new QHBoxLayout;
    QCheckBox* checkBox = new QCheckBox;

    QTextEdit* text = new QTextEdit(inputText);
    QSize size = ui_newGoal->document()->size().toSize();
    text->setFixedHeight(size.height());
    text->setReadOnly(true);
    text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(checkBox);
    layout->addWidget(text);

    ui_goalsLayout->addLayout(layout,0);
    connect(checkBox, &QCheckBox::clicked, [=]() {fncCompleteGoal(layout);});
}

void UserTab::uiInit()
{

    ui_goals = new QWidget;
    ui_newGoal = new QTextEdit;
    ui_btnAddGoal = new QPushButton("add Goal");

    ui_goalsLayout = new QVBoxLayout();
    ui_goalsLayout->setAlignment(Qt::AlignTop);
    ui_goals->setLayout(ui_goalsLayout);

    QScrollArea* scroller = new QScrollArea;
    scroller->setMinimumHeight(200);
    scroller->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroller->setWidgetResizable(true);
    scroller->setWidget(ui_goals);

    ui_mainLayout = new QVBoxLayout;
    ui_mainLayout->addWidget(scroller);
    ui_mainLayout->addWidget(ui_newGoal);
    ui_mainLayout->addWidget(ui_btnAddGoal);
    setLayout(ui_mainLayout);
}

void UserTab::fncCompleteGoal(QHBoxLayout* chkBox)
{
    QWidget* text = chkBox->itemAt(1)->widget();
    QFont f;
    if (!isDone)
    {
        f.setStrikeOut(true);
        isDone = true;
    }
    else
    {
        f.setStrikeOut(false);
        isDone = false;
    }
    text->setFont(f);
    qDebug() << "Check";
}
