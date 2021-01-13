#ifndef COURSEUI_H
#define COURSEUI_H

#include <QWidget>
#include "header.h"

namespace Ui {
class CourseUI;
}

class CourseUI : public QWidget
{
    Q_OBJECT

public:
    explicit CourseUI(QWidget *parent = 0);
    ~CourseUI();

    void init();

private slots:
    void query_course(int pos);
    void on_t2_add_pushButton_clicked();
    void on_t3_info_change(int pos);
    void on_t4_pushButton_clicked();

    void on_t3_m_pushButton_clicked();

private:
    Ui::CourseUI *ui;

    QMap<QString, QString> course_name_to_no;
    QMap<QString, QString> course_no_to_name;

    QList<QString> course_no_list;
};

#endif // COURSEUI_H
