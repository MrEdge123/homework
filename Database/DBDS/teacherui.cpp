#include "teacherui.h"
#include "ui_teacherui.h"

TeacherUI::TeacherUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherUI)
{
    ui->setupUi(this);
}

TeacherUI::~TeacherUI()
{
    delete ui;
}

void TeacherUI::init()
{
    QGridLayout *playout = new QGridLayout(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString sql = "select no, name from teacher";

    db.open();

    //teacher
    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        teacher_name_to_no.clear();

        while(ret.next()) {
            QString name = ret.value("no").toString() + " (" + ret.value("name").toString() + ")";
            QString no = ret.value("no").toString();

            QCheckBox *pbox = new QCheckBox(name, this);

            teacher_name_to_no.insert(name, no);
            playout->addWidget(pbox);
        }
    }

    //sdpet
    sql = "select no, name from sdept ";
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        ui->t1_sdept_comboBox->clear();
        ui->t2_sdept_comboBox->clear();
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

    //ui
    ui->t2_q_no_lineEdit->setText("");
    ui->t2_no_lineEdit->setText("");
    ui->t2_birth_dateEdit->setEnabled(false);
    ui->t2_direction_lineEdit->setEnabled(false);
    ui->t2_job_title_lineEdit->setEnabled(false);
    ui->t2_m_pushButton->setEnabled(false);
    ui->t2_name_lineEdit->setEnabled(false);
    ui->t2_sdept_comboBox->setEnabled(false);
    ui->t2_sex_comboBox->setEnabled(false);

    db.close();

    QLayoutItem *child;

    if(ui->t3_scrollAreaWidgetContents->layout()) {
        while( (child = ui->t3_scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
            if(child->widget()) {
                child->widget()->setParent(NULL);
            }
            delete child;
        }
        delete ui->t3_scrollAreaWidgetContents->layout();
    }

    ui->t3_scrollArea->widget()->setLayout(playout);
}

void TeacherUI::on_t1_add_pushButton_clicked()
{
    QString no = ui->t1_no_lineEdit->text();
    QString name = ui->t1_name_lineEdit->text();
    QString sex = ui->t1_sex_comboBox->currentText();
    QString birth = ui->t1_birth_dateEdit->text();
    QString job_title = ui->t1_job_title_lineEdit->text();
    QString direction = ui->t1_direction_lineEdit->text();
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

    if(!db.open()) {
        QMessageBox::critical(NULL, "错误", db.lastError().text());
    }
    else {

        QString sql =
                "insert into user(no, password, identity) "
                "values ('%1', '%2', '%3'); "
                ;

        sql = sql.arg(no, "123456", "老师");

        QSqlQuery ret;

        if(!ret.exec(sql)) {
            QMessageBox::critical(NULL, "错误", ret.lastError().text());
        }

        sql =
                "insert into teacher(no, name, birth, sdept_no, job_title, direction, sex) "
                "values ('%1', '%2', '%3', '%4', '%5', '%6', '%7') "
                ;

        sql = sql.arg(no, name, birth, sdept_no, job_title, direction, sex);

        if(!ret.exec(sql)) {
            QMessageBox::critical(NULL, "错误", ret.lastError().text());
        }
        else {
            init();
            QMessageBox::information(this, "信息", "添加成功!");
        }
    }

    db.close();
}

void TeacherUI::on_t2_q_pushButton_clicked()
{
    QString no = ui->t2_q_no_lineEdit->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    if(!db.open()) {
        QMessageBox::critical(NULL, "错误", db.lastError().text());
    }
    else {
        QString sql =
                "select * from teacher "
                "where no = '%1' "
                ;

        sql = sql.arg(no);

        QSqlQuery ret;

        if(!ret.exec(sql)) {
            QMessageBox::critical(NULL, "错误", ret.lastError().text());
        }
        else {
            if(ret.size() == 0) {
                QMessageBox::critical(this, "错误", "该用户不存在");
            }
            else {
                ret.next();

                ui->t2_birth_dateEdit->setEnabled(true);
                ui->t2_direction_lineEdit->setEnabled(true);
                ui->t2_job_title_lineEdit->setEnabled(true);
                ui->t2_m_pushButton->setEnabled(true);
                ui->t2_name_lineEdit->setEnabled(true);
                ui->t2_sdept_comboBox->setEnabled(true);
                ui->t2_sex_comboBox->setEnabled(true);

                QString time = ret.value("birth").toString();
                QString name = ret.value("name").toString();
                QString sex = ret.value("sex").toString();
                QString sdept_no = ret.value("sdept_no").toString();
                QString job_title = ret.value("job_title").toString();
                QString direction = ret.value("direction").toString();

                ui->t2_no_lineEdit->setText(no);
                ui->t2_birth_dateEdit->setDate(QDate::fromString(time, "yyyy-MM-dd"));
                ui->t2_name_lineEdit->setText(name);
                ui->t2_sex_comboBox->setCurrentText(sex);
                ui->t2_sdept_comboBox->setCurrentText(sdept_no_to_name[sdept_no]);
                ui->t2_direction_lineEdit->setText(direction);
                ui->t2_job_title_lineEdit->setText(job_title);
            }
        }
    }
}

void TeacherUI::on_t2_m_pushButton_clicked()
{
    QString no = ui->t2_no_lineEdit->text();
    QString name = ui->t2_name_lineEdit->text();
    QString sex = ui->t2_sex_comboBox->currentText();
    QString birth = ui->t2_birth_dateEdit->text();
    QString job_title = ui->t2_job_title_lineEdit->text();
    QString direction = ui->t2_direction_lineEdit->text();
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
    QSqlQuery ret;

    sql =
            "update teacher "
            "set name = '%1', sex = '%2', birth = '%3', sdept_no = '%4', job_title = '%5', direction = '%6' "
            "where no = '%7'; "
            ;

    sql = sql.arg(name, sex, birth, sdept_no,  job_title, direction, no);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        db.commit();
        init();
        QMessageBox::information(this, "信息", "修改成功!");
    }

    db.close();
}

void TeacherUI::on_t3_pushButton_clicked()
{
    if(QMessageBox::Yes == QMessageBox::warning(this, "警告", "确定要删除选定教职工?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No)) {
        qDebug() << "yes";
    }
    else {
        qDebug() << "no";
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    db.open();

    QLayout *layout = ui->t3_scrollAreaWidgetContents->layout();

    for(int i = 0; i < layout->count(); i++) {
        QLayoutItem *it = layout->itemAt(i);
        QCheckBox *pbox = qobject_cast<QCheckBox *>(it->widget());

        if(!pbox->isChecked()) continue;

        QString sql;

        sql =   "delete from teacher "
                "where no = '%1'; "
                ;

        sql = sql.arg(teacher_name_to_no[pbox->text()]);

        QSqlQuery ret;
        if(!ret.exec(sql)) {
            QMessageBox::critical(this, "错误", ret.lastError().text());
        }
        else {
            db.commit();
        }
    }

    db.close();

    init();
    QMessageBox::information(this, "信息", "删除完成!");
}
