#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString user, QString identity) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->user = user;
    this->identity = identity;
    this->setWindowTitle(QString("教务管理系统 ") + "用户:" + user + " 身份:" + identity);

    student_action = new QAction(this);
    sdept_action = new QAction(this);
    course_action = new QAction(this);
    teacher_action = new QAction(this);
    teacher_course_action = new QAction(this);
    score_action = new QAction(this);
    query_action = new QAction(this);
    statistic_action = new QAction(this);

    student_action->setText("学生管理");
    sdept_action->setText("系信息管理");
    teacher_action->setText("教职工管理");
    course_action->setText("课程管理");
    teacher_course_action->setText("选课管理");
    score_action->setText("成绩管理");
    query_action->setText("信息查询");
    statistic_action->setText("统计报表");

    ui->menubar->addAction(student_action);
    ui->menubar->addAction(sdept_action);
    ui->menubar->addAction(teacher_action);
    ui->menubar->addAction(course_action);
    ui->menubar->addAction(teacher_course_action);
    ui->menubar->addAction(score_action);
    ui->menubar->addAction(query_action);
    ui->menubar->addAction(statistic_action);

    welcome_ui = new WelcomeUI(this);
    student_ui = new StudentUI(this);
    sdept_ui = new SdeptUI(this);
    teacher_ui = new TeacherUI(this);
    course_ui = new CourseUI(this);
    tc_ui = new TCUI(this);
    score_ui = new ScoreUI(this);
    static_ui = new StatisticUI(this);
    message_ui = new MessageUI(this);

    changePd_ui = new ChangPdUI(this, user);

    connect(ui->exitLogin_action, SIGNAL(triggered(bool)), this, SLOT(exit_login()));
    connect(ui->changePD_action, SIGNAL(triggered(bool)), this, SLOT(change_to_pd_ui()));

    ui->stackedWidget->addWidget(welcome_ui);
    ui->stackedWidget->addWidget(student_ui);
    ui->stackedWidget->addWidget(sdept_ui);
    ui->stackedWidget->addWidget(teacher_ui);
    ui->stackedWidget->addWidget(course_ui);
    ui->stackedWidget->addWidget(tc_ui);
    ui->stackedWidget->addWidget(score_ui);
    ui->stackedWidget->addWidget(static_ui);
    ui->stackedWidget->addWidget(message_ui);

    ui->stackedWidget->addWidget(changePd_ui);

    ui->stackedWidget->setCurrentWidget(welcome_ui);

    connect(student_action, SIGNAL(triggered(bool)), this, SLOT(change_to_student_ui()));
    connect(sdept_action, SIGNAL(triggered(bool)), this, SLOT(change_to_sdept_ui()));
    connect(teacher_action, SIGNAL(triggered(bool)), this, SLOT(change_to_teacher_ui()));
    connect(course_action, SIGNAL(triggered(bool)), this, SLOT(change_to_course_ui()));
    connect(teacher_course_action, SIGNAL(triggered(bool)), this, SLOT(change_to_tc_ui()));
    connect(score_action, SIGNAL(triggered(bool)), this, SLOT(change_to_score_ui()));
    connect(statistic_action, SIGNAL(triggered(bool)), this, SLOT(change_to_static_ui()));
    connect(query_action, SIGNAL(triggered(bool)), this, SLOT(change_to_message_ui()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit_login()
{
    emit exit_login_sig();
}

void MainWindow::change_to_student_ui()
{
    qDebug() << "change to student ui";
    ui->stackedWidget->setCurrentWidget(student_ui);
    student_ui->init();
}

void MainWindow::change_to_sdept_ui()
{
    ui->stackedWidget->setCurrentWidget(sdept_ui);
    sdept_ui->init();
}

void MainWindow::change_to_teacher_ui()
{
    ui->stackedWidget->setCurrentWidget(teacher_ui);
    teacher_ui->init();
}

void MainWindow::change_to_course_ui()
{
    ui->stackedWidget->setCurrentWidget(course_ui);
    course_ui->init();
}

void MainWindow::change_to_tc_ui()
{
    ui->stackedWidget->setCurrentWidget(tc_ui);
    tc_ui->init();
}

void MainWindow::change_to_score_ui()
{
    ui->stackedWidget->setCurrentWidget(score_ui);
    score_ui->init();
}

void MainWindow::change_to_static_ui()
{
    ui->stackedWidget->setCurrentWidget(static_ui);
    static_ui->init();
}

void MainWindow::change_to_message_ui()
{
    ui->stackedWidget->setCurrentWidget(message_ui);
    message_ui->init();
}

void MainWindow::change_to_pd_ui()
{
    ui->stackedWidget->setCurrentWidget(changePd_ui);
    changePd_ui->init();
}
