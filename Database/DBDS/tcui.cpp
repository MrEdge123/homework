#include "tcui.h"
#include "ui_tcui.h"

TCUI::TCUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCUI)
{
    ui->setupUi(this);
}

TCUI::~TCUI()
{
    delete ui;
}

void TCUI::init()
{

}
