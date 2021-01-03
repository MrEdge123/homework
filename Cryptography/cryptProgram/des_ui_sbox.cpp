#include "des_ui_sbox.h"
#include "ui_des_ui_sbox.h"

des_ui_sbox::des_ui_sbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::des_ui_sbox)
{
    ui->setupUi(this);

    ui->inDelta_lineEdit->setMaxLength(6);

    QRegExp regx("[0-1]+$");
    QValidator *validator = new QRegExpValidator(regx, this);

    ui->inDelta_lineEdit->setValidator(validator);

    ui->inDelta_lineEdit->setText(CLIB::num_to_bit(1, 6));
}

des_ui_sbox::~des_ui_sbox()
{
    delete ui;
}

void des_ui_sbox::on_back_button_clicked()
{
    emit back_signal("main");
}

void des_ui_sbox::print_sbox()
{
    DES des = DES();
    QString text;
    text += "SBox: S" + QString::number(sbox_num) + "\n";
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 16; j++) {
            text += QString::number(des.S[sbox_num - 1][i][j]) + ", ";
        }
        text += "\n";
    }

    QFont font = QFont();
    font.setPointSize(14);
    ui->sbox_textBrowser->setFont(font);
    ui->sbox_textBrowser->setText(text);
}

void des_ui_sbox::on_S1_pushButton_clicked()
{
    this->sbox_num = 1;
    print_sbox();
}

void des_ui_sbox::on_S2_pushButton_clicked()
{
    this->sbox_num = 2;
    print_sbox();
}

void des_ui_sbox::on_S3_pushButton_clicked()
{
    this->sbox_num = 3;
    print_sbox();
}

void des_ui_sbox::on_S4_pushButton_clicked()
{
    this->sbox_num = 4;
    print_sbox();
}

void des_ui_sbox::on_S5_pushButton_clicked()
{
    this->sbox_num = 5;
    print_sbox();
}

void des_ui_sbox::on_S6_pushButton_clicked()
{
    this->sbox_num = 6;
    print_sbox();
}

void des_ui_sbox::on_S7_pushButton_clicked()
{
    this->sbox_num = 7;
    print_sbox();
}

void des_ui_sbox::on_S8_pushButton_clicked()
{
    this->sbox_num = 8;
    print_sbox();
}

void des_ui_sbox::on_onceSbox_pushButton_clicked()
{
    if(sbox_num == 0) {
        QMessageBox::critical(this, "错误", "未选定S盒!");
        return;
    }

    UINT inDelta = ui->inDelta_lineEdit->text().toInt(NULL, 2);
    ui->inDelta_lineEdit->setText(CLIB::num_to_bit(inDelta, 6));

    DES des = DES();
    vector<UINT> ans[16];
    for(UINT in = 0; in < (1 << 6); in++) {
        UINT in2 = in ^ inDelta;
        UINT out = des.Once_SBox(sbox_num - 1, in) ^ des.Once_SBox(sbox_num - 1, in2);
        ans[out].push_back(in);
    }

    QString text;
    text += "当前S盒: " + QString("S") + QString::number(sbox_num) + "\n";

    text += "输入输出情况: \n";
    for(UINT i = 0; i < 16; i++) {

        text += "输出: " + CLIB::num_to_bit(i, 4) + "\n";
        text += "数量: " + QString::number(ans[i].size()) + "\n";

        if(ans[i].size() == 0) {
            text += "\n";
            continue;
        }

        text += "输入:\n";

        for(int j = 0; j < (int)ans[i].size() - 1; j++) {
            text += CLIB::num_to_bit(ans[i][j], 6) + ", ";
        }
        text += CLIB::num_to_bit(ans[i][ans[i].size()-1], 6);

        text += "\n\n";

    }

    QFont font = QFont();
    font.setPointSize(10);
    ui->sbox_textBrowser->setFont(font);
    ui->sbox_textBrowser->setText(text);
}

void des_ui_sbox::on_mode_button_clicked()
{
    emit back_signal("des_change");
}
