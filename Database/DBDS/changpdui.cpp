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
                    init();
                    QMessageBox::information(this, "信息", "修改成功!");
                }
            }
        }
    }
}
