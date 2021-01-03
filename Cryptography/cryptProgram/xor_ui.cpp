#include "xor_ui.h"
#include "ui_xor_ui.h"

XOR_UI::XOR_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XOR_UI)
{
    ui->setupUi(this);
}

XOR_UI::~XOR_UI()
{
    delete ui;
}

void XOR_UI::on_back_button_clicked()
{
    emit back_signal("main");
}

void XOR_UI::on_srcFilePath_button_clicked()
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

void XOR_UI::on_dstFilePath_button_clicked()
{
    QString FileName = QFileDialog::getSaveFileName(this);
    ui->dstFilePath_lineEdit->setText(FileName);
}

void XOR_UI::on_genKey_button_clicked()
{
    int charLen = 126 - 32;
    QString key;
    for(int i = 0; i < 32; i++) {
        key += rand() % charLen + 32;
    }
    ui->keyString_lineEdit->setText(key);
}

void XOR_UI::on_encrypt_button_clicked()
{
    QString srcFilePath = ui->srcFilePath_lineEdit->text();
    QString dstFilePath = ui->dstFilePath_lineEdit->text();

    QFileInfo srcFileInfo(srcFilePath);
    QFileInfo dstFileInfo(dstFilePath);

    if(srcFileInfo.isFile() == false) {
        QMessageBox::critical(this, "错误",
                              QString("文件路径: " + srcFilePath + "\n" +"不存在此文件!")
                              );
        return;
    }

    if(dstFileInfo.absoluteDir().exists() == false) {
        QMessageBox::critical(this, "错误",
                              QString("输出路径: " + srcFilePath + "\n" +"输出路径错误!")
                              );
        return;
    }

    QString key = ui->keyString_lineEdit->text();

    bool ok = XOR::encrypt(srcFilePath, dstFilePath, key.toStdString().c_str());

    if(ok == false) {
        QMessageBox::critical(this, "错误",
                              QString("加密出现错误!")
                              );
        return;
    }

    QMessageBox::information(this, "信息",
                             QString("加密(解密)已完成!"));
}
