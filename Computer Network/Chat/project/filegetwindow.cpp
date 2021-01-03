#include "filegetwindow.h"
#include "ui_filegetwindow.h"
#include <QFile>

FileGetWindow::FileGetWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileGetWindow)
{
    QFile qssfile(":/qss/source/StyleSheet.qss");
    bool ok = qssfile.open(QFile::ReadOnly);
    if(ok) setStyleSheet(qssfile.readAll());

    ui->setupUi(this);
}

FileGetWindow::~FileGetWindow()
{
    delete ui;
}

void FileGetWindow::setLabel(QString text)
{
    ui->label->setText(text);
}

void FileGetWindow::on_pushButton_clicked()
{
    QString fileDir = QFileDialog::getExistingDirectory(this);
    if(fileDir.isEmpty()) return;
    emit accept(fileDir);
}

void FileGetWindow::on_pushButton_2_clicked()
{
    this->hide();
    emit reject();
}
