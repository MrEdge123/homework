#include "elgamal_ui.h"
#include "ui_elgamal_ui.h"

ELGAMAL_UI::ELGAMAL_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ELGAMAL_UI)
{
    ui->setupUi(this);
    elgamal = new ELGamal();

    ui->generate_PG_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->gen_private_key_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->gen_public_key_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->generate_M_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->generate_K_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->calculate_U_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->encrypt_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->calculate_V_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->decrypt_lineEdit->setFocusPolicy(Qt::NoFocus);
}

ELGAMAL_UI::~ELGAMAL_UI()
{
    delete ui;
}

void ELGAMAL_UI::on_back_button_clicked()
{
    emit back_signal("main");
}

void ELGAMAL_UI::on_generate_PG_button_clicked()
{
    std::pair<UINT, UINT> pg = elgamal->generate_PG();
    QString text;
    text += "<p, g> = <" + QString::number(pg.first) + ", ";
    text += QString::number(pg.second) + ">";
    ui->generate_PG_lineEdit->setText(text);
    ui->gen_private_key_button->setEnabled(true);
    ui->generate_M_button->setEnabled(true);
    ui->generate_K_button->setEnabled(true);
}

void ELGAMAL_UI::on_gen_private_key_button_clicked()
{
    UINT d = elgamal->gen_private_key();
    QString text;
    text += "d = " + QString::number(d);
    ui->gen_private_key_lineEdit->setText(text);
    ui->gen_public_key_button->setEnabled(true);
}

void ELGAMAL_UI::on_gen_public_key_button_clicked()
{
    UINT y = elgamal->gen_public_key();
    QString text;
    text += "y = g^d = " + QString::number(y) + " (mod p)";
    ui->gen_public_key_lineEdit->setText(text);

    if(ui->generate_K_lineEdit->text() != "") {
        ui->calculate_U_button->setEnabled(true);
    }
}

void ELGAMAL_UI::on_generate_M_button_clicked()
{
    UINT M = elgamal->generate_M();
    QString text;
    text += "M = " + QString::number(M);
    ui->generate_M_lineEdit->setText(text);

    if(ui->calculate_U_lineEdit->text() != "") {
        ui->encrypt_button->setEnabled(true);
    }
}

void ELGAMAL_UI::on_generate_K_button_clicked()
{
    UINT K = elgamal->generate_K();
    QString text;
    text += "k = " + QString::number(K);
    ui->generate_K_lineEdit->setText(text);
    if(ui->gen_public_key_lineEdit->text() != "") {
        ui->calculate_U_button->setEnabled(true);
    }
}

void ELGAMAL_UI::on_calculate_U_button_clicked()
{
    UINT U = elgamal->calculate_U();
    QString text;
    text += "U = y^k = " + QString::number(U) + " (mod p)";
    ui->calculate_U_lineEdit->setText(text);

    if(ui->generate_M_lineEdit->text() != "") {
        ui->encrypt_button->setEnabled(true);
    }
}

void ELGAMAL_UI::on_encrypt_button_clicked()
{
    std::pair<UINT, UINT> pr = elgamal->encrypt();
    QString text;
    text += "<g^k % p, U*M % p> = <" + QString::number(pr.first) + ", ";
    text += QString::number(pr.second) + ">";
    ui->encrypt_lineEdit->setText(text);

    ui->calculate_V_button->setEnabled(true);
}

void ELGAMAL_UI::on_calculate_V_button_clicked()
{
    UINT V = elgamal->calculate_V();
    QString text;
    text += "V = C1^d = " + QString::number(V) + " (mod p)";
    ui->calculate_V_lineEdit->setText(text);

    ui->decrypt_button->setEnabled(true);
}

void ELGAMAL_UI::on_decrypt_button_clicked()
{
    UINT M = elgamal->decrypt();
    QString text;
    text += "M = C2*V^(-1) = " + QString::number(M) + " (mod p)";
    ui->decrypt_lineEdit->setText(text);
}
