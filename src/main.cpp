#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("QDiary");
    QCoreApplication::setOrganizationName("QDiary");
    app.setWindowIcon(QIcon("../images/QDiary.ico"));
    MainWindow w;
    w.setWindowTitle("QDiary");
    w.show();

    return app.exec();
}
