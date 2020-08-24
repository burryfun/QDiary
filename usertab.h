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


class UserTab : public QWidget
{
    Q_OBJECT
public:
    explicit UserTab(QWidget *parent = nullptr);

signals:

public slots:
    void fncAddGoal();

private:

    std::vector<QString> newGoals;

    QWidget* goals;
    QTextEdit* newGoal;
    QPushButton* btnAddGoal;
    QVBoxLayout* goalsLayout;
    QVBoxLayout* mainLayout;
};

#endif // USERTAB_H
