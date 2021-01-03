#include "short_en.h"
#include "ui_short_en.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

SHORT_EN::SHORT_EN(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SHORT_EN)
{
    ui->setupUi(this);

    ui->key_lineEdit->setMaxLength(64);

    QRegExp regx("[0-1]+$");
    QValidator *validator = new QRegExpValidator(regx, this);

    ui->key_lineEdit->setValidator(validator);
}

SHORT_EN::~SHORT_EN()
{
    delete ui;
}

void SHORT_EN::on_back_button_clicked()
{
    emit back_signal("main");
}

void SHORT_EN::on_srcFilePath_button_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this);
    ui->srcFilePath_lineEdit->setText(FileName);

    if(FileName.size() == 0) return;

    QFileInfo FileInfo = QFileInfo(FileName);
    QString name = FileInfo.completeBaseName();
    QString suff = FileInfo.suffix();
    QString path = FileInfo.absolutePath();

    name += "_crypt";

    FileName = path + "/" + name + "." + suff;

    ui->dstFilePath_lineEdit->setText(FileName);
}

void SHORT_EN::on_dstFilePath_button_clicked()
{
    QString FileName = QFileDialog::getSaveFileName(this);
    ui->dstFilePath_lineEdit->setText(FileName);
}

void SHORT_EN::on_mode1_radioButton_clicked()
{
    mode = 1;
}

void SHORT_EN::on_mode2_radioButton_clicked()
{
    mode = 2;
}

void SHORT_EN::on_mode3_radioButton_clicked()
{
    mode = 3;
}

void SHORT_EN::on_genKey_button_clicked()
{
    ULL key = CLIB::generate_bit(64);
    ui->key_lineEdit->setText(CLIB::num_to_bit(key, 64));
}

void SHORT_EN::on_encrypt_button_clicked()
{
    crypt(true);
}

void SHORT_EN::on_decrypt_button_clicked()
{
    crypt(false);
}

void SHORT_EN::crypt(bool isEncrypt)
{
    QString src_path = ui->srcFilePath_lineEdit->text();
    QString dst_path = ui->dstFilePath_lineEdit->text();

    QFileInfo inputFile(src_path);
    QFileInfo outputFile(dst_path);

    //选择的文件不存在
    if(!inputFile.exists()) {
        QMessageBox::critical(this, "错误", "选择的文件不存在!");
        return;
    }

    //qDebug() << "flag1";

    //保存路径文件夹不存在
    if(!outputFile.dir().exists()) {
        //qDebug() << "flag2";
        QMessageBox::critical(this, "错误", "保存路径文件夹不存在!");
        return;
    }

    //qDebug() << "flag3";

    QString str = ui->key_lineEdit->text();
    while(str.length() < 64) str.append('0');
    ui->key_lineEdit->setText(str);

    ULL key = str.toULongLong(NULL, 2);

    DES tmp_des(src_path, dst_path, key, isEncrypt, mode);

    QString msg = isEncrypt ? "已完成加密!\n" : "已完成解密!\n";
    if(isEncrypt) {
        msg += "加密前的大小: " +
                QString::number(QFileInfo(src_path).size()) + "B\n";
        msg += "加密后的大小: " +
                QString::number(QFileInfo(dst_path).size()) + "B\n";
    }
    else {
        msg += "解密前的大小: " +
                QString::number(QFileInfo(src_path).size()) + "B\n";
        msg += "解密后的大小: " +
                QString::number(QFileInfo(dst_path).size()) + "B\n";
    }

    QMessageBox::information(this, "信息", msg);
}
