#include "scoreui.h"
#include "ui_scoreui.h"

ScoreUI::ScoreUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreUI)
{
    ui->setupUi(this);
}

ScoreUI::~ScoreUI()
{
    delete ui;
}

void ScoreUI::init()
{

}
