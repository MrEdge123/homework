#ifndef DES_UI_CHANGE_H
#define DES_UI_CHANGE_H

#include <QWidget>
#include <QMessageBox>
#include <vector>
#include "des.h"

namespace Ui {
class DES_UI_CHANGE;
}

class DES_UI_CHANGE : public QWidget
{
    Q_OBJECT

signals:
    void back_signal(QString str);

public:
    explicit DES_UI_CHANGE(QWidget *parent = 0);
    ~DES_UI_CHANGE();

private slots:
    void on_back_button_clicked();

    void on_mode_button_clicked();

    void on_run_button_clicked();

    void on_constKey_button_clicked();

    void on_constMsg_button_clicked();

    void on_runCnt_radioButton_clicked();

    void on_runCnt1_radioButton_clicked();

    void on_runCnt10_radioButton_clicked();

    void on_runCnt100_radioButton_clicked();

private:
    Ui::DES_UI_CHANGE *ui;

    bool const_status = 1;
    int runCnt = 1;
};

#endif // DES_UI_CHANGE_H
