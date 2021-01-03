#include "fileprogresswindow.h"
#include "ui_fileprogresswindow.h"
#include <QFile>

FileProgressWindow::FileProgressWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileProgressWindow)
{
    QFile qssfile(":/qss/source/StyleSheet.qss");
    bool ok = qssfile.open(QFile::ReadOnly);
    if(ok) setStyleSheet(qssfile.readAll());

    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
}

FileProgressWindow::~FileProgressWindow()
{
    delete ui;
}

void FileProgressWindow::setLabel(QString text)
{
    ui->label->setText(text);
}

void FileProgressWindow::setValue(int value)
{
    ui->progressBar->setValue(value);
}
