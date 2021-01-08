#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("教务管理系统");

    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
    mw = NULL;
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_pushButton_clicked()
{
    QString user = ui->user_lineEdit->text();
    QString password = ui->password_lineEdit->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString user_sql =
            "select * from user "
            "where no = '%1' "
            ;

    QString login_sql =
            "select * from user "
            "where no = '%1' and password = '%2' "
            ;

    user_sql = user_sql.arg(user);
    login_sql = login_sql.arg(user, password);

    qDebug() << "user_sql: " << user_sql;
    qDebug() << "login_sql: " << login_sql;

    if(!db.open()) {
        QMessageBox::critical(this, "数据库打开错误", db.lastError().text());
    }
    else {
        QSqlQuery ret;
        if(!ret.exec(user_sql)) {
            QMessageBox::critical(this, "user_sql执行错误", ret.lastError().text());
        }
        else {
            if(ret.size() == 0) {
                 QMessageBox::critical(this, "错误", "该用户不存在!");
            }
            else {
                if(!ret.exec(login_sql)) {
                    QMessageBox::critical(this, "login_sql执行错误", ret.lastError().text());
                }
                else {
                    if(ret.size() == 0) {
                        QMessageBox::critical(this, "错误", "密码输入错误!");
                    }
                    else {
                        //获取身份信息
                        ret.next();
                        QString identity = ret.value("identity").toString();

                        if(identity != QString("管理员")) {
                            QMessageBox::critical(this, "错误", "无权限访问系统!");
                        }
                        else {
                            //进入主界面
                            mw = new MainWindow(NULL, user, identity);
                            mw->show();
                            this->hide();

                            connect(mw, SIGNAL(exit_login_sig()), this, SLOT(relogin()));
                        }
                    }
                }
            }
        }
    }
}

void Login::relogin()
{
    mw->deleteLater();
    ui->user_lineEdit->setText("");
    ui->password_lineEdit->setText("");
    this->show();
    qDebug() << "relogin";
}

void Login::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter) {
        on_login_pushButton_clicked();
    }
}
