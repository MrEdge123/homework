#include "statisticui.h"
#include "ui_statisticui.h"

StatisticUI::StatisticUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticUI)
{
    ui->setupUi(this);
}

StatisticUI::~StatisticUI()
{
    delete ui;
}

void StatisticUI::init()
{

}

void StatisticUI::on_radioButton_pressed()
{
    QStringList header;
    header << "学号" << "姓名" << "性别" << "课程号" << "课程名" << "教职工号" << "教师名" << "上课时间"
           << "上课地点" << "学时" << "学分" << "考试时间" << "平时成绩" << "考试成绩" << "总评成绩";

    ui->t1_tableWidget->setColumnCount(header.count());
    ui->t1_tableWidget->setHorizontalHeaderLabels(header);

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
                "select student.no, student.name, student.sex,  "
                "       course.no, course.name, teacher.no, teacher.name,  "
                "       class_time, class_location, course.hour, course.credit, exam_time  "
                "       usual_score, exam_score, student_course.score  "
                "from student, course, teacher_course, student_course, teacher "
                "where student.no = student_course.student_no and "
                "      student_course.tc_no = teacher_course.no and  "
                "      teacher_course.teacher_no = teacher.no and       "
                "      teacher_course.course_no = course.no             "
                "order by student.no; "
                ;

        QSqlQuery ret;
        if(!ret.exec(sql)) {
            QMessageBox::critical(NULL, "错误", ret.lastError().text());
        }
        else {

            while(ret.next()) {


            }
        }
    }

    db.close();
}
