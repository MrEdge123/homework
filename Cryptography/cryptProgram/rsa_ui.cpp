#include "rsa_ui.h"
#include "ui_rsa_ui.h"

RSA_UI::RSA_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSA_UI)
{
    ui->setupUi(this);
    rsa = new RSA();

    ui->generate_PQ_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->calculate_N_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->calculate_PHI_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->generate_E_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->generate_D_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->generate_M_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->decrypt_lineEdit->setFocusPolicy(Qt::NoFocus);
}

RSA_UI::~RSA_UI()
{
    delete ui;
}

void RSA_UI::on_back_button_clicked()
{
    emit back_signal("main");
}

void RSA_UI::on_generate_PQ_button_clicked()
{
    std::pair<UINT, UINT> pq = rsa->generate_PQ();
    QString text;
    text += "p = " + QString::number(pq.first) + ", ";
    text += "q = " + QString::number(pq.second);
    ui->generate_PQ_lineEdit->setText(text);

    ui->calculate_N_button->setEnabled(true);
}

void RSA_UI::on_calculate_N_button_clicked()
{
    ULL n = rsa->calculate_N();
    QString text;
    text += "n = p*q = " + QString::number(n);
    ui->calculate_N_lineEdit->setText(text);

    ui->calculate_PHI_button->setEnabled(true);
    ui->generate_M_button->setEnabled(true);
}

void RSA_UI::on_calculate_PHI_button_clicked()
{
    ULL PHI = rsa->calculate_PHI();
    QString text;
    text += "φ(n) = (p-1)*(q-1) = " + QString::number(PHI);
    ui->calculate_PHI_lineEdit->setText(text);

    ui->generate_E_button->setEnabled(true);
}

void RSA_UI::on_generate_E_button_clicked()
{
    ULL E = rsa->generate_E();
    QString text;
    text += "e = " + QString::number(E) + ", ";
    text += "gcd(e, φ(n)) = 1";
    ui->generate_E_lineEdit->setText(text);

    ui->generate_D_button->setEnabled(true);
}

void RSA_UI::on_generate_D_button_clicked()
{
    ULL D = rsa->generate_D();
    QString text;
    text += "d = e^(-1) = " + QString::number(D) + " (mod φ(n))";
    ui->generate_D_lineEdit->setText(text);

    if(ui->generate_M_lineEdit->text() != "") {
        ui->encrypt_button->setEnabled(true);
    }
}

void RSA_UI::on_generate_M_button_clicked()
{
    ULL M = rsa->generate_M();
    QString text;
    text += "M = " + QString::number(M);
    ui->generate_M_lineEdit->setText(text);

    if(ui->generate_D_lineEdit->text() != "") {
        ui->encrypt_button->setEnabled(true);
    }
}

void RSA_UI::on_encrypt_button_clicked()
{
    ULL C = rsa->encrypt();
    QString text;
    text += "C = M^e = " + QString::number(C)  + " (mod n)";
    ui->encrypt_lineEdit->setText(text);

    ui->decrypt_button->setEnabled(true);
}

void RSA_UI::on_decrypt_button_clicked()
{
    ULL M = rsa->decrypt();
    QString text;
    text += "M = C^d = " + QString::number(M) + " (mod n)";
    ui->decrypt_lineEdit->setText(text);
}
