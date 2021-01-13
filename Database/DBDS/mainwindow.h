#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QAction>

#include "studentui.h"
#include "welcomeui.h"
#include "sdeptui.h"
#include "teacherui.h"
#include "courseui.h"
#include "tcui.h"
#include "scoreui.h"
#include "statisticui.h"
#include "changpdui.h"
#include "messageui.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QString user = "", QString identity = "");
    ~MainWindow();

signals:
    void exit_login_sig();

private slots:
    void exit_login();
    void change_to_student_ui();
    void change_to_sdept_ui();
    void change_to_teacher_ui();
    void change_to_course_ui();
    void change_to_tc_ui();
    void change_to_score_ui();
    void change_to_static_ui();
    void change_to_message_ui();

    void change_to_pd_ui();

private:
    Ui::MainWindow *ui;
    QString user;
    QString identity;

    QAction *student_action;
    QAction *sdept_action;
    QAction *course_action;
    QAction *teacher_action;
    QAction *teacher_course_action;
    QAction *score_action;
    QAction *query_action;
    QAction *statistic_action;

    StudentUI *student_ui;
    WelcomeUI *welcome_ui;
    SdeptUI *sdept_ui;
    TeacherUI *teacher_ui;
    CourseUI *course_ui;
    TCUI *tc_ui;
    ScoreUI *score_ui;
    StatisticUI *static_ui;
    MessageUI *message_ui;

    ChangPdUI *changePd_ui;
};

#endif // MAINWINDOW_H
