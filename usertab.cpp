#include "usertab.h"

UserTab::UserTab(QWidget *parent) : QWidget(parent)
{
    QWidget* goals = new QWidget;

    goalsLayout = new QVBoxLayout();
    goalsLayout->setAlignment(Qt::AlignTop);

    newGoal = new QTextEdit;
    btnAddGoal = new QPushButton("add Goal");


    goals->setLayout(goalsLayout);
    mainLayout = new QVBoxLayout;

    QScrollArea* scroller = new QScrollArea;
    scroller->setMinimumHeight(200);
    scroller->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroller->setWidgetResizable(true);
    scroller->setWidget(goals);

    mainLayout->addWidget(scroller);
    mainLayout->addWidget(newGoal);
    mainLayout->addWidget(btnAddGoal);
    setLayout(mainLayout);

    connect(btnAddGoal, &QPushButton::clicked, this, &UserTab::fncAddGoal);
}


void UserTab::fncAddGoal()
{
    QHBoxLayout* layout = new QHBoxLayout;
    QCheckBox* checkBox = new QCheckBox;

    QString inputText = newGoal->toPlainText();
    QTextEdit* text = new QTextEdit(inputText);

    QSize size = newGoal->document()->size().toSize();
    text->setFixedHeight(size.height());
    text->setReadOnly(true);
    text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(checkBox);
    layout->addWidget(text);

    goalsLayout->addLayout(layout);
}
