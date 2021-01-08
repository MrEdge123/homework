#ifndef CHANGPDUI_H
#define CHANGPDUI_H

#include <QWidget>

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QKeyEvent>

namespace Ui {
class ChangPdUI;
}

class ChangPdUI : public QWidget
{
    Q_OBJECT

public:
    explicit ChangPdUI(QWidget *parent = 0, QString no = "");
    ~ChangPdUI();

    void init();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangPdUI *ui;
    QString no;
};

#endif // CHANGPDUI_H
