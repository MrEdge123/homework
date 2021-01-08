#include "statisticui.h"
#include "ui_statisticui.h"

StatisticUI::StatisticUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticUI)
{
    ui->setupUi(this);
}

StatisticUI::~StatisticUI()
{
    delete ui;
}

void StatisticUI::init()
{

}
