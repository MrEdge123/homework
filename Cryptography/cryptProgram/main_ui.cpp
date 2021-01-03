#include "main_ui.h"
#include "ui_main_ui.h"

MAIN_UI::MAIN_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MAIN_UI)
{
    ui->setupUi(this);
}

MAIN_UI::~MAIN_UI()
{
    delete ui;
}

void MAIN_UI::on_des_button_clicked()
{
    emit back_signal("des");
}

void MAIN_UI::on_xor_button_clicked()
{
    emit back_signal("xor");
}

void MAIN_UI::on_dh_button_clicked()
{
    emit back_signal("dh");
}

void MAIN_UI::on_elgamal_button_clicked()
{
    emit back_signal("elgamal");
}

void MAIN_UI::on_rsa_button_clicked()
{
    emit back_signal("rsa");
}

void MAIN_UI::on_short_en_button_clicked()
{
    emit back_signal("short_en");
}
