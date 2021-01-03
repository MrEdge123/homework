#include "filesendwindow.h"
#include "ui_filesendwindow.h"
#include <QFile>

FileSendWindow::FileSendWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSendWindow)
{
    QFile qssfile(":/qss/source/StyleSheet.qss");
    bool ok = qssfile.open(QFile::ReadOnly);
    if(ok) setStyleSheet(qssfile.readAll());

    ui->setupUi(this);

}

FileSendWindow::~FileSendWindow()
{
    delete ui;
}

void FileSendWindow::setLabel(QString text)
{
    ui->label->setText(text);
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
}

void FileSendWindow::on_pushButton_clicked()
{
    ui->label->setText("等待对方允许...");
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);

    emit accept();
}

void FileSendWindow::on_pushButton_2_clicked()
{
    this->hide();
}
