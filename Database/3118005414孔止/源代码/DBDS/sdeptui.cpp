#include "sdeptui.h"
#include "ui_sdeptui.h"

SdeptUI::SdeptUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SdeptUI)
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(query_sdept(int)));
    connect(ui->t3_no_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_t3_info_change(int)));
}

SdeptUI::~SdeptUI()
{
    delete ui;
}

void SdeptUI::init()
{
    ui->listWidget->clear();
    ui->t3_no_comboBox->clear();

    QGridLayout *playout = new QGridLayout(this);

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
        sdept_no_list.clear();

        while(ret.next()) {
            QString name = ret.value("no").toString() + " (" + ret.value("name").toString() + ")";
            QString no = ret.value("no").toString();

            QCheckBox *pbox = new QCheckBox(name, this);

            sdept_name_to_no.insert(name, no);
            sdept_no_to_name.insert(no, name);
            sdept_no_list.append(no);
            playout->addWidget(pbox);

            ui->listWidget->addItem(name);
        }
    }

    db.close();

    QLayoutItem *child;

    if(ui->t4_scrollAreaWidgetContents->layout()) {
        while( (child = ui->t4_scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
            if(child->widget()) {
                child->widget()->setParent(NULL);
            }
            delete child;
        }
        delete ui->t4_scrollAreaWidgetContents->layout();
    }

    /*
    for(int i = ui->t4_scrollAreaWidgetContents->layout()->count()-1; i >= 0; i--) {
        QLayoutItem *it = ui->t4_scrollAreaWidgetContents->layout()->takeAt(i);
        QCheckBox *pbox = qobject_cast<QCheckBox*>(it->widget());
        delete it;
    }
    */

    ui->t4_scrollArea->widget()->setLayout(playout);

    foreach (QString no, sdept_no_list) {
        ui->t3_no_comboBox->addItem(no);
    }
}

void SdeptUI::query_sdept(int pos)
{
    if(pos < 0) return;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString sql =
            "select * from sdept "
            "where no = '%1' "
            ;

    sql = sql.arg(sdept_no_list[pos]);

    db.open();

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        ret.next();

        QString no = ret.value("no").toString();
        QString name = ret.value("name").toString();
        QString introduction = ret.value("introduction").toString();

        ui->t1_no_lineEdit->setText(no);
        ui->t1_name_lineEdit->setText(name);
        ui->t1_introduction_textBrowser->setText(introduction);
    }

    db.close();
}

void SdeptUI::on_t2_add_pushButton_clicked()
{
    QString no = ui->t2_no_lineEdit->text();
    QString name = ui->t2_name_lineEdit->text();
    QString introduction = ui->t2_introduction_textEdit->toPlainText();

    if(no == "") {
        QMessageBox::critical(this, "错误", "系号为空");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "系名为空");
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString sql =
            "insert into sdept(no, name, introduction) "
            "values ('%1', '%2', '%3'); "
            ;

    sql = sql.arg(no, name, introduction);

    db.open();

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        db.commit();
        QMessageBox::information(this, "信息", "添加成功!");
        init();
    }

    db.close();
}

void SdeptUI::on_t3_info_change(int pos)
{
    if(pos < 0) return;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    QString sql =
            "select * from sdept "
            "where no = '%1' "
            ;

    sql = sql.arg(sdept_no_list[pos]);

    db.open();

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        ret.next();

        QString name = ret.value("name").toString();
        QString introduction = ret.value("introduction").toString();

        ui->t3_name_lineEdit->setText(name);
        ui->t3_introduction_textEdit->setText(introduction);
    }

    db.close();
}

void SdeptUI::on_t3_m_pushButton_clicked()
{
    QString no = ui->t3_no_comboBox->currentText();
    QString name = ui->t3_name_lineEdit->text();
    QString introduction = ui->t3_introduction_textEdit->toPlainText();

    if(sdept_no_to_name.find(no) == sdept_no_to_name.end()) {
        QMessageBox::critical(this, "错误", "系号错误");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "系别为空");
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    db.open();

    QString sql;

    sql =   "update sdept "
            "set name = '%1', introduction = '%2' "
            "where no = '%3'; "
            ;

    sql = sql.arg(name, introduction, no);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        db.commit();
        QMessageBox::information(this, "信息", "修改成功!");
    }

    db.close();
}

void SdeptUI::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");               //数据库服务器ip
    db.setUserName("root");                    //数据库用户名
    db.setPassword("123456");                  //密码
    db.setDatabaseName("education_system");    //使用哪个数据库

    db.open();

    QLayout *layout = ui->t4_scrollAreaWidgetContents->layout();

    for(int i = 0; i < layout->count(); i++) {
        QLayoutItem *it = layout->itemAt(i);
        QCheckBox *pbox = qobject_cast<QCheckBox *>(it->widget());

        if(!pbox->isChecked()) continue;

        QString sql;

        sql =   "delete from sdept "
                "where no = '%1'; "
                ;

        sql = sql.arg(sdept_name_to_no[pbox->text()]);

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
