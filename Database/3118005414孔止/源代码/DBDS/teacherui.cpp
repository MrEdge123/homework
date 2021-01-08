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
