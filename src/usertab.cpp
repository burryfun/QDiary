#include "usertab.h"

// + ADD CHECK OF REPEAT DATES IN LISTGOALS

UserTab::UserTab(QString name, QWidget *parent) : QWidget(parent), nameTab(name)
{
    uiInit();

}

const QString UserTab::getName() const
{
    return nameTab;
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
//    QFile file(fileName);
//    file.open(QFile::ReadOnly | QFile::Text);
//    QTextStream in(&file);
//    QString line;
//    while(!in.atEnd())
//    {
//        in.readLineInto(&line);
//        if (line == nameTab)
//        {
//            in.readLineInto(&line);
//            while(line != (nameTab+"End"))
//            {
//                if (line.split(":")[1] == UNCOMPLETED)
//                {
//                    fncAddGoal(line.split(":")[0]);
//                }
//                else
//                {
//                    fncAddGoal(line.split(":")[0], Qt::Checked);
//                }
//                in.readLineInto(&line);
//            }
//            break;
//        }
//        else
//        {
//            in.readLineInto(&line);
//        }
//    }
}

void UserTab::uiInit()
{
    // INITIALIZATION BASE LIST OF GOALS AND BUTTON
    ui_listGoals = new QComboBox;

    ui_btnAddListGoals = new QPushButton("add new list of goals");

    ui_mainLayout = new QVBoxLayout;
    ui_mainLayout->setAlignment(Qt::AlignTop);
    ui_mainLayout->addWidget(ui_listGoals);
    ui_mainLayout->addWidget(ui_btnAddListGoals);
    setLayout(ui_mainLayout);

    // INITTIALIZATION HIDDEN UI FOR GOALS

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

    ui_newGoal->setVisible(false);
    ui_btnAddGoal->setVisible(false);
    ui_mainLayout->addWidget(scroller);
    ui_mainLayout->addWidget(ui_newGoal);
    ui_mainLayout->addWidget(ui_btnAddGoal);

    connect(ui_btnAddListGoals, &QPushButton::clicked, this, &UserTab::fncAddListGoals);
    connect(ui_listGoals, QOverload<int>::of(&QComboBox::activated), [=](int index){ fncChangeList(index); });

}

void UserTab::uiInitGoals()
{

}

void UserTab::fncAddListGoals()
{
    static int i = 0;
    i++;
    if (nameTab == Ui::YEARTAB)
    {
        QString currentDate = date.currentDate().toString("yyyy");
        ui_listGoals->addItem(currentDate);
        listGoals[currentDate + QString::number(i)];
    }
    if (nameTab == Ui::MONTHTAB)
    {
        QString currentDate = date.currentDate().toString("MMMM");
        ui_listGoals->addItem(currentDate);
    }
    if (nameTab == Ui::WEEKTAB)
    {
        int day = date.currentDate().day();
        QString currentDate = QString::number((day % 7) + 1) + " week";
        ui_listGoals->addItem(currentDate);
    }
    if (nameTab == Ui::DAYTAB)
    {
        QString currentDate = date.currentDate().toString("dddd");
        ui_listGoals->addItem(currentDate);
    }
    fncChangeList(ui_listGoals->count() - 1);
    ui_listGoals->setCurrentIndex(ui_listGoals->count() - 1);
}

void UserTab::fncChangeList(int index)
{
    qDebug() << index;
    // ПРОЧИТАТЬ ИЗ ФАЙЛА ПО ДАТЕ, КОТОРАЯ ЧИТАЕТСЯ ИЗ ИНДЕКСА COMBOBOX
//    ui_listGoals->itemText(index);
//    qDebug() << ui_listGoals->itemText(index);

    // DIRTY HACK
    delete ui_btnAddGoal;
    ui_btnAddGoal = new QPushButton("Add Goal");
    ui_mainLayout->addWidget(ui_btnAddGoal);

    ui_newGoal->setVisible(true);
    ui_btnAddGoal->setVisible(true);
    clearLayout(ui_goalsLayout);

    // SHOW GOALS FROM LIST TO UI
    for (const auto& goal : listGoals[ui_listGoals->itemText(index)])
    {
        fncAddGoal(goal.first, index);
    }

    connect(ui_btnAddGoal, &QPushButton::clicked, [=]()
    {
        fncAddGoal(QString::number(listGoals[ui_listGoals->itemText(ui_listGoals->currentIndex())].size() + 1) +
                                    ". " + ui_newGoal->toPlainText(), index);
    });
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

// PLEASE DELETE INDEX ARG////////////////////////////////
void UserTab::fncAddGoal(const QString& inputText, const int index, const Qt::CheckState& state)
// ///////////////////////////////////////////////////////
{
    qDebug() << index;
//    goals[inputText] = UNCOMPLETED;
    listGoals[ui_listGoals->itemText(ui_listGoals->currentIndex())][inputText] = UNCOMPLETED;

    //add goal in UI
    QHBoxLayout* layout = new QHBoxLayout;
    QCheckBox* checkBox = new QCheckBox;
    QPushButton* deleteBtn = new QPushButton;

    // write text from textEditor to new goal
    QTextEdit* text = new QTextEdit(inputText);
    QSize size = ui_newGoal->document()->size().toSize();
    text->setFixedHeight(size.height());
    text->setReadOnly(true);
    text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    deleteBtn->setText("Delete");

    if (state == Qt::Checked)
    {
//        goals[inputText] = COMPLETED;
        listGoals[ui_listGoals->itemText(index)][inputText] = COMPLETED;
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
