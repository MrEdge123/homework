#include "changpdui.h"
#include "ui_changpdui.h"

ChangPdUI::ChangPdUI(QWidget *parent, QString no) :
    QWidget(parent),
    ui(new Ui::ChangPdUI)
{
    ui->setupUi(this);
    this->no = no;
}

ChangPdUI::~ChangPdUI()
{
    delete ui;
}

void ChangPdUI::init()
{
    ui->new_password_lineEdit->setText("");
    ui->old_password_lineEdit->setText("");
    ui->confirm_password_lineEdit->setText("");
}

void ChangPdUI::on_pushButton_clicked()
{
    QString user = no;
    QString password = ui->old_password_lineEdit->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    if(!db.open()) {
        QMessageBox::critical(this, "数据库打开错误", db.lastError().text());
    }
    else {
        QString sql =
                "select * from user "
                "where no = '%1' and password = '%2' "
                ;

        sql = sql.arg(user, password);

        QSqlQuery ret;
        if(!ret.exec(sql)) {
            QMessageBox::critical(this, "sql执行错误", ret.lastError().text());
        }
        else {
            if(ret.size() == 0) {
                QMessageBox::critical(this, "错误", "旧密码错误!");
            }
            else {
                if(ui->new_password_lineEdit->text() != ui->confirm_password_lineEdit->text()) {
                    QMessageBox::critical(this, "错误", "密码不一致!");
                }
                else {
                    sql = "update user "
                          "set password = '%1' "
                          "where no = '%2' "
                            ;

                    sql = sql.arg(ui->new_password_lineEdit->text(), no);

                    if(!ret.exec(sql)) {
                        QMessageBox::critical(this, "sql执行错误", ret.lastError().text());
                    }
                    else {
                        db.commit();
                        init();
                        QMessageBox::information(this, "信息", "修改成功!");
                    }
                }
            }
        }
    }

    db.close();
}
