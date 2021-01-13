#ifndef TEACHERUI_H
#define TEACHERUI_H

#include <QWidget>
#include "header.h"

namespace Ui {
class TeacherUI;
}

class TeacherUI : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherUI(QWidget *parent = 0);
    ~TeacherUI();

    void init();

private slots:
    void on_t1_add_pushButton_clicked();

    void on_t2_q_pushButton_clicked();

    void on_t2_m_pushButton_clicked();

    void on_t3_pushButton_clicked();

private:
    Ui::TeacherUI *ui;

    QMap<QString, QString> teacher_name_to_no;

    QMap<QString, QString> sdept_name_to_no;
    QMap<QString, QString> sdept_no_to_name;
};

#endif // TEACHERUI_H
