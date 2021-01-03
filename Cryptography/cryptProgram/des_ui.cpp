#include "des_ui.h"
#include "ui_des_ui.h"

DES_UI::DES_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DES_UI)
{
    ui->setupUi(this);

    ui->msg_lineEdit->setMaxLength(64);
    ui->key_lineEdit->setMaxLength(64);

    ui->encrypt_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->decrypt_lineEdit->setFocusPolicy(Qt::NoFocus);

    QRegExp regx("[0-1]+$");
    QValidator *validator = new QRegExpValidator(regx, this);

    ui->msg_lineEdit->setValidator(validator);
    ui->key_lineEdit->setValidator(validator);
}

DES_UI::~DES_UI()
{
    delete ui;
}

void DES_UI::on_back_button_clicked()
{
    emit back_signal("main");
}

void DES_UI::on_genMsg_button_clicked()
{
    ULL key = DES::generate_64bit();
    QString str = QString::number(key, 2);

    while(str.size() < 64)
        str.prepend('0');

    ui->msg_lineEdit->setText(str);
}

void DES_UI::on_genKey_button_clicked()
{
    ULL key = DES::generate_64bit();
    QString str = QString::number(key, 2);

    while(str.size() < 64)
        str.prepend('0');

    ui->key_lineEdit->setText(str);
}

void DES_UI::on_encrypt_button_clicked()
{
    ULL msg = ui->msg_lineEdit->text().toULongLong(NULL, 2);
    ULL key = ui->key_lineEdit->text().toULongLong(NULL, 2);

    ui->msg_lineEdit->setText(CLIB::num_to_bit(msg, 64));
    ui->key_lineEdit->setText(CLIB::num_to_bit(key, 64));

    DES des(msg, key);

    ULL cpt = des.get_ans_msg();
    QString str = QString::number(cpt, 2);

    while(str.size() < 64)
        str.prepend('0');

    ui->encrypt_lineEdit->setText(str);
}

void DES_UI::on_decrypt_button_clicked()
{
    ULL msg = ui->encrypt_lineEdit->text().toULongLong(NULL, 2);
    ULL key = ui->key_lineEdit->text().toULongLong(NULL, 2);

    ui->encrypt_lineEdit->setText(CLIB::num_to_bit(msg, 64));
    ui->key_lineEdit->setText(CLIB::num_to_bit(key, 64));

    DES des(msg, key, -1);

    ULL cpt = des.get_ans_msg();
    QString str = QString::number(cpt, 2);

    while(str.size() < 64)
        str.prepend('0');

    ui->decrypt_lineEdit->setText(str);
}

void DES_UI::on_mode_button_clicked()
{
    emit back_signal("des_sbox");
}
