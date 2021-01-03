#ifndef DES_UI_SBOX_H
#define DES_UI_SBOX_H

#include <QWidget>
#include <QMessageBox>
#include <vector>
#include "des.h"

namespace Ui {
class des_ui_sbox;
}

class des_ui_sbox : public QWidget
{
    Q_OBJECT

signals:
    void back_signal(QString str);

public:
    explicit des_ui_sbox(QWidget *parent = 0);
    ~des_ui_sbox();

private slots:
    void on_back_button_clicked();

    void print_sbox();

    void on_S1_pushButton_clicked();

    void on_S2_pushButton_clicked();

    void on_S3_pushButton_clicked();

    void on_S4_pushButton_clicked();

    void on_S5_pushButton_clicked();

    void on_S6_pushButton_clicked();

    void on_S7_pushButton_clicked();

    void on_S8_pushButton_clicked();

    void on_onceSbox_pushButton_clicked();

    void on_mode_button_clicked();

private:
    Ui::des_ui_sbox *ui;

    int sbox_num = 0;
};

#endif // DES_UI_SBOX_H
