#ifndef LOGIN_H
#define LOGIN_H

#include "mainwindow.h"

#include <QWidget>

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QKeyEvent>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_login_pushButton_clicked();
    void relogin();

protected:
    virtual void keyPressEvent(QKeyEvent *ev);

private:
    Ui::Login *ui;
    MainWindow *mw;

    QSqlDatabase db;
};

#endif // LOGIN_H
