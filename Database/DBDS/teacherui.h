#ifndef TEACHERUI_H
#define TEACHERUI_H

#include <QWidget>

#include <QMap>
#include <QString>
#include <QList>

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QLayout>
#include <QCheckBox>
#include <QLayoutItem>
#include <QObject>

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
