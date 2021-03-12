#include "loginwindow.h"
#include "chatwindow.h"
#include "listwindow.h"
#include "user.h"
#include <QApplication>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QFile>
#include <exception>

int main(int argc, char *argv[])
{
    /*
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
            QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
            */

    QApplication a(argc, argv);
    LoginWindow w1;

    //QFile qssfile(":/qss/source/StyleSheet.qss");
    //bool ok = qssfile.open(QFile::ReadOnly);
    //if(ok) w1.setStyleSheet(qssfile.readAll());

    w1.show();

    return a.exec();

    return 0;
}
