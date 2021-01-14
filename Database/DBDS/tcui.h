#ifndef TCUI_H
#define TCUI_H

#include <QWidget>
#include "header.h"

namespace Ui {
class TCUI;
}

class TCUI : public QWidget
{
    Q_OBJECT

public:
    explicit TCUI(QWidget *parent = 0);
    ~TCUI();

    void init();

private slots:
    void on_t1_teacher_comboBox_currentTextChanged(const QString &arg1);
    void on_t1_teacher_listWidget_currentTextChanged(const QString &currentText);
    void on_t1_tc_no_listWidget_currentTextChanged(const QString &currentText);

    void on_t2_teacher_comboBox_currentTextChanged(const QString &arg1);
    void on_t2_teacher_listWidget_currentTextChanged(const QString &currentText);
    void on_t2_tc_no_listWidget_currentTextChanged(const QString &currentText);
    void on_t2_m_pushButton_clicked();

    void on_t2_exam_time_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_t3_teacher_comboBox_currentTextChanged(const QString &arg1);

    void on_t3_teacher_listWidget_currentTextChanged(const QString &currentText);

    void on_t3_not_select_course_comboBox_currentTextChanged(const QString &arg1);

    void on_t3_select_course_listWidget_currentTextChanged(const QString &currentText);

    void on_t3_delete_pushButton_clicked();

    void on_t3_add_pushButton_clicked();

private:
    Ui::TCUI *ui;
};

#endif // TCUI_H
