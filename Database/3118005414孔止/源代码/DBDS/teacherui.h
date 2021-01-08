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

private:
    Ui::TeacherUI *ui;

    QMap<QString, QString> teacher_name_to_no;
};

#endif // TEACHERUI_H
