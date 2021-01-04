#include "mainwindow.h"
#include <QApplication>

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

void test() {
    qDebug() << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");    //数据库服务器ip
    db.setUserName("root");         //数据库用户名
    db.setPassword("123456");       //密码
    db.setDatabaseName("world");    //使用哪个数据库

    if(!db.open()) {
        QMessageBox::critical(NULL, "错误", db.lastError().text());
    }
    else {
        db.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    test();

    return a.exec();
}
