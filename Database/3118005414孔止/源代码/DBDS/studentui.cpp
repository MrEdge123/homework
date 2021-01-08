#include "studentui.h"
#include "ui_studentui.h"

StudentUI::StudentUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentUI)
{
    ui->setupUi(this);
}

StudentUI::~StudentUI()
{
    delete ui;
}

void StudentUI::init()
{
    ui->t1_birth_dateEdit->setTime(QTime::currentTime());
    ui->t1_name_lineEdit->setText("");
    ui->t1_no_lineEdit->setText("");
    ui->t1_score_lineEdit->setText("");
    ui->t1_sdept_comboBox->clear();
    ui->t1_sex_comboBox->setCurrentIndex(0);

    ui->t2_birth_dateEdit->setTime(QTime::currentTime());
    ui->t2_name_lineEdit->setText("");
    ui->t2_no_lineEdit->setText("");
    ui->t2_q_no_lineEdit->setText("");
    ui->t2_score_lineEdit->setText("");
    ui->t2_sex_comboBox->setCurrentIndex(0);

    ui->t2_birth_dateEdit->setEnabled(false);
    ui->t2_m_pushButton->setEnabled(false);
    ui->t2_name_lineEdit->setEnabled(false);
    ui->t2_score_lineEdit->setEnabled(false);
    ui->t2_sdept_comboBox->setEnabled(false);
    ui->t2_sex_comboBox->setEnabled(false);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString sql = "select * from sdept";

    db.open();

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        sdept_name_to_no.clear();
        sdept_no_to_name.clear();

        while(ret.next()) {
            QString name = ret.value("no").toString() + " (" + ret.value("name").toString() + ")";
            QString no = ret.value("no").toString();

            sdept_name_to_no.insert(name, no);
            sdept_no_to_name.insert(no, name);

            ui->t1_sdept_comboBox->addItem(name);
            ui->t2_sdept_comboBox->addItem(name);
        }
    }

    db.close();
}

void StudentUI::on_t1_add_pushButton_clicked()
{
    QString no = ui->t1_no_lineEdit->text();
    QString name = ui->t1_name_lineEdit->text();
    QString sex = ui->t1_sex_comboBox->currentText();
    QString birth = ui->t1_birth_dateEdit->text();
    QString ad_score = ui->t1_score_lineEdit->text();
    QString sdept_no;

    if(no == "") {
        QMessageBox::critical(this, "错误", "学号为空");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "姓名为空");
        return;
    }

    if(sdept_name_to_no.find(ui->t1_sdept_comboBox->currentText())
            == sdept_name_to_no.end()) {
        QMessageBox::critical(this, "错误", "系别输入错误");
        return;
    }

    sdept_no = sdept_name_to_no[ui->t1_sdept_comboBox->currentText()];

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString sql =
            "insert into user(no, password, identity) "
            "values ('%1', '%2', '%3'); "
            ;

    sql = sql.arg(no, "123456", "学生");

    db.open();

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        db.commit();

        sql = "insert into student(no, name, sex, birth, ad_score, sdept_no) "
              "values ('%1', '%2', '%3', '%4', %5, '%6'); "
                ;

        sql = sql.arg(no, name, sex, birth, ad_score, sdept_no);

        if(!ret.exec(sql)) {
            QMessageBox::critical(this, "错误", ret.lastError().text());
        }
        else {
            db.commit();
            QMessageBox::information(this, "信息", "添加成功!");
            init();
        }
    }

    db.close();
}

void StudentUI::on_t2_q_pushButton_clicked()
{
    QString no = ui->t2_q_no_lineEdit->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString sql =
            "select * from student "
            "where no = '%1'; "
            ;

    sql = sql.arg(no);

    db.open();

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 0) {
            QMessageBox::critical(this, "错误", "用户号不存在!");
        }
        else {
            ret.next();
            ui->t2_no_lineEdit->setText(no);

            QString time = ret.value("birth").toString();
            QString name = ret.value("name").toString();
            QString sex = ret.value("sex").toString();
            QString score = ret.value("ad_score").toString();
            QString sdept_no = ret.value("sdept_no").toString();

            //qDebug() << time;
            //qDebug() << QDate::fromString(time, "yyyy-MM-dd");

            ui->t2_birth_dateEdit->setEnabled(true);
            ui->t2_m_pushButton->setEnabled(true);
            ui->t2_name_lineEdit->setEnabled(true);
            ui->t2_score_lineEdit->setEnabled(true);
            ui->t2_sdept_comboBox->setEnabled(true);
            ui->t2_sex_comboBox->setEnabled(true);

            ui->t2_birth_dateEdit->setDate(QDate::fromString(time, "yyyy-MM-dd"));
            ui->t2_name_lineEdit->setText(name);
            ui->t2_sex_comboBox->setCurrentText(sex);
            ui->t2_sdept_comboBox->setCurrentText(sdept_no_to_name[sdept_no]);
            ui->t2_score_lineEdit->setText(score);
        }
    }

    db.close();
}

void StudentUI::on_t2_m_pushButton_clicked()
{
    QString no = ui->t2_no_lineEdit->text();
    QString name = ui->t2_name_lineEdit->text();
    QString sex = ui->t2_sex_comboBox->currentText();
    QString birth = ui->t2_birth_dateEdit->text();
    QString ad_score = ui->t2_score_lineEdit->text();
    QString sdept_no;

    if(sdept_name_to_no.find(ui->t2_sdept_comboBox->currentText())
            == sdept_name_to_no.end()) {
        QMessageBox::critical(this, "错误", "系别输入错误");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "姓名为空");
        return;
    }

    sdept_no = sdept_name_to_no[ui->t2_sdept_comboBox->currentText()];

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    db.open();

    QString sql;

    sql = "select no from student "
          "where no = '%1' "
            ;

    sql = sql.arg(no);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 0) {
            QMessageBox::critical(this, "错误", "该用户不存在");
            db.close();
            return;
        }
    }

    sql =
            "update student "
            "set name = '%1', sex = '%2', birth = '%3', ad_score = '%4', sdept_no = '%5' "
            "where no = '%6'; "
            ;

    sql = sql.arg(name, sex, birth, ad_score, sdept_no, no);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        db.commit();
        QMessageBox::information(this, "信息", "修改成功!");
    }

    db.close();
}
