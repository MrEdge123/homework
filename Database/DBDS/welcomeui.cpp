#include "welcomeui.h"
#include "ui_welcomeui.h"

WelcomeUI::WelcomeUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeUI)
{
    ui->setupUi(this);
}

WelcomeUI::~WelcomeUI()
{
    delete ui;
}
