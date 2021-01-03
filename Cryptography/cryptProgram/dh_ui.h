#ifndef DH_UI_H
#define DH_UI_H

#include <QWidget>
#include "dh.h"

namespace Ui {
class DH_UI;
}

class DH_UI : public QWidget
{
    Q_OBJECT

signals:
    void back_signal(QString str);

public:
    explicit DH_UI(QWidget *parent = 0);
    ~DH_UI();

private slots:
    void on_back_button_clicked();

    void on_generate_PG_button_clicked();

    void on_generate_Akey_button_clicked();

    void on_generate_Bkey_button_clicked();

    void on_send_ga_button_clicked();

    void on_send_gb_button_clicked();

    void on_cal_A_share_key_button_clicked();

    void on_cal_B_share_key_button_clicked();

private:
    Ui::DH_UI *ui;
    DH *dh;
};

#endif // DH_UI_H
