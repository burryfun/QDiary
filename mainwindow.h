#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QBoxLayout>
#include <QMessageBox>
#include <QSettings>
#include <QScreen>
#include <QFileDialog>
#include <QApplication>
#include <QCloseEvent>

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
    void createActions();
    bool maybeSave();
    void setCurrentFile(const QString&);
    bool saveFile(const QString& fileName);
    void loadFile(const QString& fileName);
    void readSettings();
    void writeSettings();


    QFile file;
    QString curFile;

    Ui::MainWindow *ui;
    std::vector<UserTab*> tabs;

};

#endif // MAINWINDOW_H
