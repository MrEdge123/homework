#ifndef RSA_UI_H
#define RSA_UI_H

#include <QWidget>
#include "rsa.h"

namespace Ui {
class RSA_UI;
}

class RSA_UI : public QWidget
{
    Q_OBJECT

signals:
    void back_signal(QString str);

public:
    explicit RSA_UI(QWidget *parent = 0);
    ~RSA_UI();

private slots:
    void on_back_button_clicked();

    void on_generate_PQ_button_clicked();

    void on_calculate_N_button_clicked();

    void on_calculate_PHI_button_clicked();

    void on_generate_E_button_clicked();

    void on_generate_D_button_clicked();

    void on_generate_M_button_clicked();

    void on_encrypt_button_clicked();

    void on_decrypt_button_clicked();

private:
    Ui::RSA_UI *ui;
    RSA *rsa;
};

#endif // RSA_UI_H
