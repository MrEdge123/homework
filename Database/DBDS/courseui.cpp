#include "courseui.h"
#include "ui_courseui.h"

CourseUI::CourseUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseUI)
{
    ui->setupUi(this);

    connect(ui->t1_listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(query_course(int)));
    connect(ui->t3_no_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_t3_info_change(int)));
}

CourseUI::~CourseUI()
{
    delete ui;
}

void CourseUI::init()
{
    //ui
    ui->t1_listWidget->clear();
    ui->t2_no_lineEdit->setText("");
    ui->t2_name_lineEdit->setText("");
    ui->t2_hour_lineEdit->setText("");
    ui->t2_credit_lineEdit->setText("");
    ui->t3_no_comboBox->clear();
    ui->t3_name_lineEdit->setText("");
    ui->t3_hour_lineEdit->setText("");
    ui->t3_credit_lineEdit->setText("");

    QGridLayout *playout = new QGridLayout(this);   //t4

    QString sql = "select no, name from course ";

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        course_name_to_no.clear();
        course_no_to_name.clear();
        course_no_list.clear();

        while(ret.next()) {
            QString name = ret.value("no").toString() + " (" + ret.value("name").toString() + ")";
            QString no = ret.value("no").toString();

            course_name_to_no.insert(name, no);
            course_no_to_name.insert(no, name);
            course_no_list.append(no);

            //t1
            ui->t1_listWidget->addItem(name);

            //t3
            ui->t3_no_comboBox->addItem(no);

            //t4
            QCheckBox *pbox = new QCheckBox(name, this);
            playout->addWidget(pbox);
        }
    }

    //t4
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
    ui->t4_scrollArea->widget()->setLayout(playout);
}

void CourseUI::query_course(int pos)
{
    if(pos < 0) return;

    QString sql =
            "select * from course "
            "where no = '%1' "
            ;

    sql = sql.arg(course_no_list[pos]);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        ret.next();

        QString no = ret.value("no").toString();
        QString name = ret.value("name").toString();
        QString hour = ret.value("hour").toString();
        QString credit = ret.value("credit").toString();

        ui->t1_no_lineEdit->setText(no);
        ui->t1_name_lineEdit->setText(name);
        ui->t1_hour_lineEdit->setText(hour);
        ui->t1_credit_lineEdit->setText(credit);
    }
}

void CourseUI::on_t2_add_pushButton_clicked()
{
    QString no = ui->t2_no_lineEdit->text();
    QString name = ui->t2_name_lineEdit->text();
    QString hour = ui->t2_hour_lineEdit->text();
    QString credit = ui->t2_credit_lineEdit->text();

    if(no == "") {
        QMessageBox::critical(this, "错误", "课程号为空");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "课程名为空");
        return;
    }

    if(hour == "") hour = "null";
    if(credit == "") credit = "null";

    QString sql;
    QSqlQuery ret;

    sql =   "select no from course "
            "where no = '%1' "
            ;

    sql = sql.arg(no);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 1) {
            QMessageBox::critical(this, "错误", "课程号已存在!");
            return;
        }
    }

    sql =   "insert into course(no, name, hour, credit) "
            "values ('%1', '%2', %3, %4); "
            ;

    sql = sql.arg(no, name, hour, credit);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        init();
        QMessageBox::information(this, "信息", "添加成功!");
    }
}

void CourseUI::on_t3_info_change(int pos)
{
    if(pos < 0) return;

    QString sql =
            "select * from course "
            "where no = '%1' "
            ;

    sql = sql.arg(course_no_list[pos]);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        ret.next();

        QString name = ret.value("name").toString();
        QString hour = ret.value("hour").toString();
        QString credit = ret.value("credit").toString();

        ui->t3_name_lineEdit->setText(name);
        ui->t3_hour_lineEdit->setText(hour);
        ui->t3_credit_lineEdit->setText(credit);
    }
}

void CourseUI::on_t4_pushButton_clicked()
{
    if(QMessageBox::No == QMessageBox::warning(this, "警告", "确定要删除选定课程?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No)) {
        return;
    }

    QLayout *layout = ui->t4_scrollAreaWidgetContents->layout();

    for(int i = 0; i < layout->count(); i++) {
        QLayoutItem *it = layout->itemAt(i);
        QCheckBox *pbox = qobject_cast<QCheckBox *>(it->widget());

        if(!pbox->isChecked()) continue;

        QString sql;

        sql =   "delete from course "
                "where no = '%1'; "
                ;

        sql = sql.arg(course_name_to_no[pbox->text()]);

        QSqlQuery ret;
        if(!ret.exec(sql)) {
            QMessageBox::critical(this, "错误", ret.lastError().text());
        }
        else {
            //succ
        }
    }

    init();
    QMessageBox::information(this, "信息", "删除完成!");
}

void CourseUI::on_t3_m_pushButton_clicked()
{
    QString no = ui->t3_no_comboBox->currentText();
    QString name = ui->t3_name_lineEdit->text();
    QString hour = ui->t3_hour_lineEdit->text();
    QString credit = ui->t3_credit_lineEdit->text();

    if(course_no_to_name.find(no) == course_no_to_name.end()) {
        QMessageBox::critical(this, "错误", "课程号错误");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "课程名为空");
        return;
    }

    QString sql;

    sql =   "update course "
            "set name = '%1', hour = '%2', credit = '%3' "
            "where no = '%4'; "
            ;

    sql = sql.arg(name, hour, credit, no);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        QMessageBox::information(this, "信息", "修改成功!");
    }
}
