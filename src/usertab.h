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
#include <QFile>
#include <QFileDialog>
#include <QSaveFile>
#include <QStatusBar>
#include <algorithm>
#include <QMessageBox>
#include <QComboBox>
#include <QDate>
#include <QLocale>

#define COMPLETED "completed"
#define UNCOMPLETED "uncompleted"

using ListGoals = std::map<QString, std::map<QString, QString>>;

namespace Ui {
    class UserTab;
    const QString YEARTAB = "Year Goals";
    const QString MONTHTAB = "Month Goals";
    const QString WEEKTAB = "Week Goals";
    const QString DAYTAB = "Day Goals";
}

class UserTab : public QWidget
{
    Q_OBJECT
public:
    explicit UserTab(QString name, QWidget *parent = nullptr);
    const QString getName() const;
    void writeToFile(QSaveFile& file);
    void readFromFile(QFile& file);
    void readFromFile(const QString& fileName);
    void clear();

signals:

public slots:
    void fncAddGoal(const QString&, const int index, const Qt::CheckState& state = Qt::Unchecked);
    void fncCompleteGoal(QHBoxLayout*);
    void fncDeleteGoal(QHBoxLayout*);
    void fncAddListGoals();
    void fncChangeList(int index);

private:
    QString nameTab;
    std::map<QString, QString> goals;
    ListGoals listGoals;
    QDate date;

    void newGoal(const QString&, std::vector<QString>&);
    void completeGoal(const QString&, std::vector<QString>&);

    //UI
    void uiInit();
    void uiInitGoals();
    void clearLayout(QLayout* layout, bool deleteWidgets = true);

    QComboBox* ui_listGoals;
    QWidget* ui_goals;
    QTextEdit* ui_newGoal;
    QPushButton* ui_btnAddGoal;
    QPushButton* ui_btnAddListGoals;
    QVBoxLayout* ui_goalsLayout;
    QVBoxLayout* ui_mainLayout;
};

#endif // USERTAB_H
