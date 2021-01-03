#include "dh_ui.h"
#include "ui_dh_ui.h"
#include <QMessageBox>

DH_UI::DH_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DH_UI)
{
    ui->setupUi(this);
    dh = new DH();

    ui->generate_PG_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->generate_Akey_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->generate_Bkey_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->send_ga_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->send_gb_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->cal_A_share_key_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->cal_B_share_key_lineEdit->setFocusPolicy(Qt::NoFocus);
}

DH_UI::~DH_UI()
{
    delete ui;
}

void DH_UI::on_back_button_clicked()
{
    emit back_signal("main");
}

void DH_UI::on_generate_PG_button_clicked()
{
    std::pair<UINT, UINT> pg = dh->generate_PG();
    QString text;
    text += "<p, g> = <" + QString::number(pg.first) + ", ";
    text += QString::number(pg.second) + ">";
    ui->generate_PG_lineEdit->setText(text);
}

void DH_UI::on_generate_Akey_button_clicked()
{
    UINT a = dh->generate_Akey();
    QString text;
    text += "a = " + QString::number(a);
    ui->generate_Akey_lineEdit->setText(text);
}

void DH_UI::on_generate_Bkey_button_clicked()
{
    UINT b = dh->generate_Bkey();
    QString text;
    text += "b = " + QString::number(b);
    ui->generate_Bkey_lineEdit->setText(text);
}

void DH_UI::on_send_ga_button_clicked()
{
    if(ui->generate_PG_lineEdit->text() == "") {
        QMessageBox::critical(this, "错误", "请先生成<p, g>!");
        return;
    }
    if(ui->generate_Akey_lineEdit->text() == "") {
        QMessageBox::critical(this, "错误", "请先生成a!");
        return;
    }

    UINT ga = dh->send_ga();
    QString text;
    text += "g^a  = " + QString::number(ga) + " (mod p)";
    ui->send_ga_lineEdit->setText(text);
}

void DH_UI::on_send_gb_button_clicked()
{
    if(ui->generate_PG_lineEdit->text() == "") {
        QMessageBox::critical(this, "错误", "请先生成<p, g>!");
        return;
    }
    if(ui->generate_Bkey_lineEdit->text() == "") {
        QMessageBox::critical(this, "错误", "请先生成b!");
        return;
    }

    UINT gb = dh->send_gb();
    QString text;
    text += "g^b = " + QString::number(gb) + " (mod p)";
    ui->send_gb_lineEdit->setText(text);
}

void DH_UI::on_cal_A_share_key_button_clicked()
{
    if(ui->generate_Akey_lineEdit->text() == "") {
        QMessageBox::critical(this, "错误", "请先生成a!");
        return;
    }
    if(ui->send_gb_lineEdit->text() == "") {
        QMessageBox::critical(this, "错误", "请先发送g^b!");
        return;
    }

    UINT key = dh->cal_A_share_key();
    QString text;
    text += "key: (g^b)^a = g^(ab) = " + QString::number(key) + " (mod p)";
    ui->cal_A_share_key_lineEdit->setText(text);
}

void DH_UI::on_cal_B_share_key_button_clicked()
{
    if(ui->generate_Bkey_lineEdit->text() == "") {
        QMessageBox::critical(this, "错误", "请先生成b!");
        return;
    }
    if(ui->send_ga_lineEdit->text() == "") {
        QMessageBox::critical(this, "错误", "请先发送g^a!");
        return;
    }

    UINT key = dh->cal_B_share_key();
    QString text;
    text += "key: (g^a)^b = g^(ab) = " + QString::number(key) + " (mod p)";
    ui->cal_B_share_key_lineEdit->setText(text);
}
