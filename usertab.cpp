#include "usertab.h"

UserTab::UserTab(QString name, QWidget *parent) : QWidget(parent), nameTab(name)
{
    uiInit();

    connect(ui_btnAddGoal, &QPushButton::clicked, [=]() {fncAddGoal(ui_newGoal->toPlainText());});
}

void UserTab::writeToFile(QSaveFile &file)
{
    QTextStream out(&file);
    out << nameTab << endl;
    for (const auto& goal : goals)
    {
        out << goal.first << ":" << goal.second << endl;
    }
    out << nameTab + "End" << endl;
}

void UserTab::readFromFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString line;
    while(!in.atEnd())
    {
        in.readLineInto(&line);
        if (line == nameTab)
        {
            in.readLineInto(&line);
            while(line != (nameTab+"End"))
            {
                if (line.split(":")[1] == UNCOMPLETED)
                {
                    fncAddGoal(line.split(":")[0]);
                }
                else
                {
                    fncAddGoal(line.split(":")[0], Qt::Checked);
                }
                in.readLineInto(&line);
            }
            break;
        }
        else
        {
            in.readLineInto(&line);
        }
    }
}

void UserTab::uiInit()
{
    // UI INIT
    ui_goals = new QWidget;
    ui_newGoal = new QTextEdit;
    ui_btnAddGoal = new QPushButton("add Goal");

    ui_goalsLayout = new QVBoxLayout;
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

void UserTab::clear()
{
    goals.clear();
    ui_newGoal->clear();
    clearLayout(ui_goalsLayout);
}

void UserTab::clearLayout(QLayout *layout, bool deleteWidgets) {
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void UserTab::fncAddGoal(const QString& inputText, const Qt::CheckState& state)
{
    goals[inputText] = UNCOMPLETED;

    //add goal in UI
    QHBoxLayout* layout = new QHBoxLayout;
    QCheckBox* checkBox = new QCheckBox;
    QPushButton* deleteBtn = new QPushButton;

    QTextEdit* text = new QTextEdit(inputText);
    QSize size = ui_newGoal->document()->size().toSize();
    text->setFixedHeight(size.height());
    text->setReadOnly(true);
    text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    deleteBtn->setText("Delete");

    if (state == Qt::Checked)
    {
        goals[inputText] = COMPLETED;
        checkBox->setCheckState(state);
        QFont f;
        f.setStrikeOut(true);
        text->setFont(f);
    }
    layout->addWidget(checkBox);
    layout->addWidget(text);
    layout->addWidget(deleteBtn);

    ui_goalsLayout->addLayout(layout, 1);
    connect(checkBox, &QCheckBox::clicked, [=]() {fncCompleteGoal(layout);});
    connect(deleteBtn, &QPushButton::clicked, [=]() {fncDeleteGoal(layout);});
}

void UserTab::fncCompleteGoal(QHBoxLayout* layout)
{
    // COMPLETE GOAL
    QWidget* textArea = layout->itemAt(1)->widget();
    QString text = dynamic_cast<QTextEdit*>(textArea)->toPlainText();
    bool isDone = !dynamic_cast<QCheckBox*>(layout->itemAt(0)->widget())->isChecked();
    QFont f;

    if (!isDone)
    {
        // SETUP COMPLETE FLAG IN goals
        goals[text] = COMPLETED;

        // STRIKEOUT GOAL IN UI
        f.setStrikeOut(true);
        isDone = true;
    }
    else
    {
        // REVERSE OPERATION
        goals[text] = UNCOMPLETED;
        // UI
        f.setStrikeOut(false);
        isDone = false;
    }
    textArea->setFont(f);
}

void UserTab::fncDeleteGoal(QHBoxLayout* layout)
{
    goals.erase(dynamic_cast<QTextEdit*>(layout->itemAt(1)->widget())->toPlainText());

    clearLayout(layout);
    ui_goalsLayout->removeItem(layout);
    delete layout;
}
