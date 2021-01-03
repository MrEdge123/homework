#ifndef MAIN_UI_H
#define MAIN_UI_H

#include <QWidget>
#include <QString>

namespace Ui {
class MAIN_UI;
}

class MAIN_UI : public QWidget
{
    Q_OBJECT

public:
    explicit MAIN_UI(QWidget *parent = 0);
    ~MAIN_UI();

signals:
    void back_signal(QString str);

private slots:
    void on_des_button_clicked();

    void on_xor_button_clicked();

    void on_dh_button_clicked();

    void on_elgamal_button_clicked();

    void on_rsa_button_clicked();

    void on_short_en_button_clicked();

private:
    Ui::MAIN_UI *ui;

};

#endif // MAIN_UI_H
