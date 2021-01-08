#ifndef STUDENTUI_H
#define STUDENTUI_H

#include <QWidget>
#include <QMap>
#include <QList>

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDate>

namespace Ui {
class StudentUI;
}

class StudentUI : public QWidget
{
    Q_OBJECT

public:
    explicit StudentUI(QWidget *parent = 0);
    ~StudentUI();

    void init();

private slots:


    void on_t1_add_pushButton_clicked();
    
    void on_t2_q_pushButton_clicked();

    void on_t2_m_pushButton_clicked();

private:
    Ui::StudentUI *ui;

    QMap<QString, QString> sdept_name_to_no;
    QMap<QString, QString> sdept_no_to_name;

    QList<QString> sdept_no_list;
};

#endif // STUDENTUI_H
