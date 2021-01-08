#include "login.h"
#include <QApplication>

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QFile>

void test() {
    qDebug() << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString sql =
            "select * from \n"
            "student"
            ;

    if(!db.open()) {
        QMessageBox::critical(NULL, "错误", db.lastError().text());
    }
    else {
        QSqlQuery ret;
        if(!ret.exec(sql)) {
            QMessageBox::critical(NULL, "错误", ret.lastError().text());
        }
        else {
            while(ret.next()) {
                qDebug() << ret.value("name");
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
           QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    Login w;
    w.show();

    //test();

    return a.exec();
}
