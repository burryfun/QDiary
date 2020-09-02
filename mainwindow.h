#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QBoxLayout>
#include <QMessageBox>
#include <QSettings>
#include <QtWidgets>
#include <QScreen>
#include <QFileDialog>

#include "usertab.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();

private:
    void init();
    void readSettings();
    void createActions();
    bool maybeSave();
    bool saveFile(const QString& fileName);
    void loadFile(const QString& fileName);
    void setCurrentFile(const QString&);

    QFile file;
    QString curFile;

    Ui::MainWindow *ui;
    UserTab* YearTab;
    UserTab* MonthTab;

};

#endif // MAINWINDOW_H
