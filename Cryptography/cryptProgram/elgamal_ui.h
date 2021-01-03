#ifndef ELGAMAL_UI_H
#define ELGAMAL_UI_H

#include <QWidget>
#include "elgamal.h"

namespace Ui {
class ELGAMAL_UI;
}

class ELGAMAL_UI : public QWidget
{
    Q_OBJECT

signals:
    void back_signal(QString str);

public:
    explicit ELGAMAL_UI(QWidget *parent = 0);
    ~ELGAMAL_UI();

private slots:
    void on_back_button_clicked();

    void on_generate_PG_button_clicked();

    void on_gen_private_key_button_clicked();

    void on_gen_public_key_button_clicked();

    void on_generate_M_button_clicked();

    void on_generate_K_button_clicked();

    void on_calculate_U_button_clicked();

    void on_encrypt_button_clicked();

    void on_calculate_V_button_clicked();

    void on_decrypt_button_clicked();

private:
    Ui::ELGAMAL_UI *ui;
    ELGamal *elgamal;
};

#endif // ELGAMAL_UI_H
