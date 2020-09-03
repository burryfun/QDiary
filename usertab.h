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
#include <QThread>
#include <QMessageBox>

#define COMPLETED "completed"
#define UNCOMPLETED "uncompleted"

class UserTab : public QWidget
{
    Q_OBJECT
public:

    explicit UserTab(QString name, QWidget *parent = nullptr);
    void writeToFile(QSaveFile& file);
    void readFromFile(QFile& file);
    void readFromFile(const QString& fileName);
    void clear();

signals:

public slots:
    void fncAddGoal(const QString&, const Qt::CheckState& state = Qt::Unchecked);
    void fncCompleteGoal(QHBoxLayout*);
    void fncDeleteGoal(QHBoxLayout*);

private:

    QString nameTab;
    std::map<QString, QString> goals;



    void newGoal(const QString&, std::vector<QString>&);
    void completeGoal(const QString&, std::vector<QString>&);


    //UI
    void uiInit();
    void clearLayout(QLayout* layout, bool deleteWidgets = true);

    QWidget* ui_goals;
    QTextEdit* ui_newGoal;
    QPushButton* ui_btnAddGoal;
    QVBoxLayout* ui_goalsLayout;
    QVBoxLayout* ui_mainLayout;

};

#endif // USERTAB_H
