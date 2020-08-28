#ifndef USERTAB_H
#define USERTAB_H

#include <QWidget>
#include <QBoxLayout>
#include <QCheckBox>
#include <QTextEdit>
#include <QPushButton>
#include <QAction>
#include <QScrollBar>
#include <QDial>
#include <QScrollArea>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QGroupBox>
#include <QFormLayout>
#include <QSize>
#include <QDebug>

class UserTab : public QWidget
{
    Q_OBJECT
public:
    explicit UserTab(QWidget *parent = nullptr);

signals:

public slots:
    void fncAddGoal();
    void fncCompleteGoal(QHBoxLayout*);

private:

    std::vector<QString> goals;
    std::vector<QString> completeGoals;

    void writeGoal(QString&, std::vector<QString>&);
    void removeGoal(QString&, std::vector<QString>&);

    //UI
    void uiInit();

    QWidget* ui_goals;
    QTextEdit* ui_newGoal;
    QPushButton* ui_btnAddGoal;
    QVBoxLayout* ui_goalsLayout;
    QVBoxLayout* ui_mainLayout;

    bool isDone;

};

#endif // USERTAB_H
