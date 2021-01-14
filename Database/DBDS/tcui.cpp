#include "tcui.h"
#include "ui_tcui.h"

TCUI::TCUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCUI)
{
    ui->setupUi(this);
}

TCUI::~TCUI()
{
    delete ui;
}

void TCUI::init()
{
    //ui
    //t1
    ui->t1_teacher_listWidget->clear();
    ui->t1_tc_no_listWidget->clear();
    ui->t1_class_location_lineEdit->setText("");
    ui->t1_class_time_lineEdit->setText("");
    ui->t1_course_name_lineEdit->setText("");
    ui->t1_course_no_lineEdit->setText("");
    ui->t1_exam_time_lineEdit->setText("");
    ui->t1_semester_lineEdit->setText("");
    ui->t1_tc_no_lineEdit->setText("");

    //t2
    ui->t2_teacher_listWidget->clear();
    ui->t2_tc_no_listWidget->clear();
    ui->t2_class_location_lineEdit->setText("");
    ui->t2_class_time_lineEdit->setText("");
    ui->t2_course_name_lineEdit->setText("");
    ui->t2_course_no_lineEdit->setText("");
    ui->t2_semester_lineEdit->setText("");
    ui->t2_tc_no_lineEdit->setText("");
    ui->t2_exam_time_dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->t2_exam_time_lineEdit->setText("");
    ui->t2_exam_time_dateTimeEdit->setEnabled(false);

    //t3
    ui->t3_teacher_listWidget->clear();
    ui->t3_select_course_listWidget->clear();
    ui->t3_not_select_course_listWidget->clear();
    ui->t3_tc_no_current_lineEdit->setText("");
    ui->t3_tc_no_input_lineEdit->setText("");

    QString sql;
    QSqlQuery ret;

    //t1, t2, t3: teacher_listWidget
    sql =   "select no_name from teacher_view "
            ;

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString name = ret.value("no_name").toString();
            ui->t1_teacher_listWidget->addItem(name);
            ui->t2_teacher_listWidget->addItem(name);
            ui->t3_teacher_listWidget->addItem(name);
        }
    }
}

void TCUI::on_t1_teacher_comboBox_currentTextChanged(const QString &arg1)
{
    ui->t1_teacher_listWidget->clear();

    QString sql;
    QSqlQuery ret;

    sql =   "select no_name from teacher_view "
            "where no_name like '%%1%' "
            ;

    sql = sql.arg(arg1);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString name = ret.value("no_name").toString();
            ui->t1_teacher_listWidget->addItem(name);
        }
    }
}

void TCUI::on_t1_teacher_listWidget_currentTextChanged(const QString &currentText)
{
    ui->t1_tc_no_listWidget->clear();

    QString sql;
    QSqlQuery ret;

    sql =   "select teacher_course.no "
            "from teacher_view, teacher_course "
            "where no_name = '%1' and teacher_view.no = teacher_no "
            ;

    sql = sql.arg(currentText);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString tc_no = ret.value("no").toString();
            ui->t1_tc_no_listWidget->addItem(tc_no);
        }
    }
}

void TCUI::on_t1_tc_no_listWidget_currentTextChanged(const QString &currentText)
{
    ui->t1_class_location_lineEdit->setText("");
    ui->t1_class_time_lineEdit->setText("");
    ui->t1_course_name_lineEdit->setText("");
    ui->t1_course_no_lineEdit->setText("");
    ui->t1_exam_time_lineEdit->setText("");
    ui->t1_semester_lineEdit->setText("");
    ui->t1_tc_no_lineEdit->setText("");

    QString sql;
    QSqlQuery ret;

    sql =   "select * "
            "from teacher_course, course "
            "where teacher_course.no = '%1' and course_no = course.no "
            ;

    sql = sql.arg(currentText);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString course_no = ret.value("course_no").toString();
            QString course_name = ret.value("name").toString();
            QString tc_no = currentText;
            QString semester = ret.value("semester").toString();
            QString class_time = ret.value("class_time").toString();
            QString class_location = ret.value("class_location").toString();
            QString exam_time = ret.value("exam_time").toString();

            ui->t1_class_location_lineEdit->setText(class_location);
            ui->t1_class_time_lineEdit->setText(class_time);
            ui->t1_course_name_lineEdit->setText(course_name);
            ui->t1_course_no_lineEdit->setText(course_no);
            ui->t1_semester_lineEdit->setText(semester);
            ui->t1_tc_no_lineEdit->setText(tc_no);

            QDateTime date_time = QDateTime::fromString(exam_time, "yyyy-MM-ddThh:mm:ss");
            exam_time = date_time.toString("yyyy-MM-dd hh:mm");
            ui->t1_exam_time_lineEdit->setText(exam_time);
        }
    }
}

void TCUI::on_t2_teacher_comboBox_currentTextChanged(const QString &arg1)
{
    ui->t2_teacher_listWidget->clear();

    QString sql;
    QSqlQuery ret;

    sql =   "select no_name from teacher_view "
            "where no_name like '%%1%' "
            ;

    sql = sql.arg(arg1);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString name = ret.value("no_name").toString();
            ui->t2_teacher_listWidget->addItem(name);
        }
    }
}

void TCUI::on_t2_teacher_listWidget_currentTextChanged(const QString &currentText)
{
    ui->t2_tc_no_listWidget->clear();

    QString sql;
    QSqlQuery ret;

    sql =   "select teacher_course.no "
            "from teacher_view, teacher_course "
            "where no_name = '%1' and teacher_view.no = teacher_no "
            ;

    sql = sql.arg(currentText);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString tc_no = ret.value("no").toString();
            ui->t2_tc_no_listWidget->addItem(tc_no);
        }
    }
}

void TCUI::on_t2_tc_no_listWidget_currentTextChanged(const QString &currentText)
{
    ui->t2_class_location_lineEdit->setText("");
    ui->t2_class_time_lineEdit->setText("");
    ui->t2_course_name_lineEdit->setText("");
    ui->t2_course_no_lineEdit->setText("");
    ui->t2_exam_time_lineEdit->setText("");
    ui->t2_semester_lineEdit->setText("");
    ui->t2_tc_no_lineEdit->setText("");

    ui->t2_exam_time_dateTimeEdit->setEnabled(true);

    QString sql;
    QSqlQuery ret;

    sql =   "select * "
            "from teacher_course, course "
            "where teacher_course.no = '%1' and course_no = course.no "
            ;

    sql = sql.arg(currentText);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString course_no = ret.value("course_no").toString();
            QString course_name = ret.value("name").toString();
            QString tc_no = currentText;
            QString semester = ret.value("semester").toString();
            QString class_time = ret.value("class_time").toString();
            QString class_location = ret.value("class_location").toString();
            QString exam_time = ret.value("exam_time").toString();

            ui->t2_class_location_lineEdit->setText(class_location);
            ui->t2_class_time_lineEdit->setText(class_time);
            ui->t2_course_name_lineEdit->setText(course_name);
            ui->t2_course_no_lineEdit->setText(course_no);
            ui->t2_semester_lineEdit->setText(semester);
            ui->t2_tc_no_lineEdit->setText(tc_no);

            QDateTime date_time = QDateTime::fromString(exam_time, "yyyy-MM-ddThh:mm:ss");
            ui->t2_exam_time_dateTimeEdit->setDateTime(date_time);
            exam_time = date_time.toString("yyyy-MM-dd hh:mm");
            ui->t2_exam_time_lineEdit->setText(exam_time);
        }
    }
}

void TCUI::on_t2_m_pushButton_clicked()
{
    QString tc_no = ui->t2_tc_no_lineEdit->text();
    QString semester = ui->t2_semester_lineEdit->text();
    QString class_time = ui->t2_class_time_lineEdit->text();
    QString class_location = ui->t2_class_location_lineEdit->text();
    QString exam_time = ui->t2_exam_time_lineEdit->text();

    QString sql;
    QSqlQuery ret;

    sql =   "update teacher_course "
            "set semester = '%2', class_time = '%3', "
            "class_location = '%4', exam_time = '%5' "
            "where no = '%1' "
            ;

    sql = sql.arg(tc_no, semester, class_time, class_location, exam_time);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        init();
        QMessageBox::information(this, "信息", "修改成功!");
    }
}

void TCUI::on_t2_exam_time_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    QString exam_time = dateTime.toString("yyyy-MM-dd hh:mm");
    ui->t2_exam_time_lineEdit->setText(exam_time);
}

void TCUI::on_t3_teacher_comboBox_currentTextChanged(const QString &arg1)
{
    ui->t3_teacher_listWidget->clear();

    QString sql;
    QSqlQuery ret;

    sql =   "select no_name from teacher_view "
            "where no_name like '%%1%' "
            ;

    sql = sql.arg(arg1);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString name = ret.value("no_name").toString();
            ui->t3_teacher_listWidget->addItem(name);
        }
    }
}

void TCUI::on_t3_teacher_listWidget_currentTextChanged(const QString &currentText)
{
    ui->t3_select_course_listWidget->clear();
    ui->t3_not_select_course_listWidget->clear();
    ui->t3_tc_no_current_lineEdit->setText("");
    ui->t3_tc_no_input_lineEdit->setText("");

    QString sql;
    QSqlQuery ret;

    sql =   "select course_view.no_name "
            "from teacher_view, course_view, teacher_course "
            "where teacher_view.no_name = '%1' and teacher_view.no = teacher_no "
            "      and course_view.no = course_no  "
            ;

    sql = sql.arg(currentText);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString name = ret.value("no_name").toString();
            ui->t3_select_course_listWidget->addItem(name);
        }
    }

    sql =   "select no_name "
            "from course_view "
            "where no not in ( "
            "   select course_view.no "
            "   from teacher_view, course_view, teacher_course "
            "   where teacher_view.no_name = '%1' and teacher_view.no = teacher_no "
            "         and course_view.no = course_no  "
            ") "
            ;

    sql = sql.arg(currentText);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString name = ret.value("no_name").toString();
            ui->t3_not_select_course_listWidget->addItem(name);
        }
    }
}

void TCUI::on_t3_not_select_course_comboBox_currentTextChanged(const QString &arg1)
{
    ui->t3_not_select_course_listWidget->clear();

    QString sql;
    QSqlQuery ret;

    sql =   "select * from ( "
            "   select no_name "
            "   from course_view "
            "   where no not in ( "
            "      select course_view.no "
            "      from teacher_view, course_view, teacher_course "
            "      where teacher_view.no_name = '%1' and teacher_view.no = teacher_no "
            "            and course_view.no = course_no  "
            "   ) "
            ") as tmp "
            "where tmp.no_name like '%%2%' "
            ;

    QString teacher_name = ui->t3_teacher_listWidget->currentItem()->text();
    QString course_name = arg1;

    sql = sql.arg(teacher_name, course_name);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString name = ret.value("no_name").toString();
            ui->t3_not_select_course_listWidget->addItem(name);
        }
    }
}

void TCUI::on_t3_select_course_listWidget_currentTextChanged(const QString &currentText)
{
    QString course_name = currentText;
    QString teacher_name = ui->t3_teacher_listWidget->currentItem()->text();

    QString sql;
    QSqlQuery ret;

    sql =   "select teacher_course.no "
            "from teacher_course, teacher_view, course_view  "
            "where teacher_view.no_name = '%1' and "
            "      course_view.no_name = '%2' and "
            "      teacher_view.no = teacher_no and "
            "      course_view.no = course_no "
            ;

    sql = sql.arg(teacher_name, course_name);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        while(ret.next()) {
            QString no = ret.value("no").toString();
            ui->t3_tc_no_current_lineEdit->setText(no);
        }
    }
}

void TCUI::on_t3_delete_pushButton_clicked()
{
    QString tc_no = ui->t3_tc_no_current_lineEdit->text();
    QString course_name = ui->t3_select_course_listWidget->currentItem()->text();
    ui->t3_tc_no_current_lineEdit->setText("");

    if(tc_no == "") {
        QMessageBox::critical(this, "错误", "未选择教职工和课程!");
        return;
    }

    QString sql;
    QSqlQuery ret;

    sql =   "delete from teacher_course "
            "where no = '%1' "
            ;

    sql = sql.arg(tc_no);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        for(int row = 0; row < ui->t3_select_course_listWidget->count(); row++) {
            QString line = ui->t3_select_course_listWidget->item(row)->text();
            if(line == course_name) {
                ui->t3_select_course_listWidget->takeItem(row);
                break;
            }
        }

        ui->t3_not_select_course_listWidget->addItem(course_name);
        int count = ui->t3_not_select_course_listWidget->count();
        ui->t3_not_select_course_listWidget->setCurrentRow(count - 1);
    }
}

void TCUI::on_t3_add_pushButton_clicked()
{
    QString course_name = ui->t3_not_select_course_listWidget->currentItem()->text();
    QString teacher_name = ui->t3_teacher_listWidget->currentItem()->text();
    QString tc_no = ui->t3_tc_no_input_lineEdit->text();
    ui->t3_tc_no_input_lineEdit->setText("");

    if(teacher_name == "") {
        QMessageBox::critical(this, "错误", "未选择教职工!");
        return;
    }

    if(course_name == "") {
        QMessageBox::critical(this, "错误", "未选择课程!");
        return;
    }

    if(tc_no == "") {
        QMessageBox::critical(this, "错误", "未输入上课号!");
        return;
    }

    QString course_no;
    QString teacher_no;

    QString sql;
    QSqlQuery ret;

    sql = "select no from teacher_view where no_name = '%1' ";
    sql = sql.arg(teacher_name);
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 0) {
            qDebug() << teacher_name;
            QMessageBox::critical(this, "错误", "教职工号查询失败");
            return;
        }
        while(ret.next()) {
            teacher_no = ret.value("no").toString();
        }
    }

    sql = "select no from course_view where no_name = '%1' ";
    sql = sql.arg(course_name);
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 0) {
            qDebug() << course_name;
            QMessageBox::critical(this, "错误", "课程号查询失败");
            return;
        }
        while(ret.next()) {
            course_no = ret.value("no").toString();
        }
    }

    qDebug() << teacher_no;
    qDebug() << course_no;

    sql =   "insert into teacher_course(no, teacher_no, course_no) "
            "values ('%1', '%2', '%3') "
            ;
    sql = sql.arg(tc_no, teacher_no, course_no);
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        for(int row = 0; row < ui->t3_not_select_course_listWidget->count(); row++) {
            QString line = ui->t3_not_select_course_listWidget->item(row)->text();
            if(line == course_name) {
                ui->t3_not_select_course_listWidget->takeItem(row);
                break;
            }
        }

        ui->t3_select_course_listWidget->addItem(course_name);
        int count = ui->t3_select_course_listWidget->count();
        ui->t3_select_course_listWidget->setCurrentRow(count - 1);
    }
}
