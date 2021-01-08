#include "courseui.h"
#include "ui_courseui.h"

CourseUI::CourseUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseUI)
{
    ui->setupUi(this);
}

CourseUI::~CourseUI()
{
    delete ui;
}

void CourseUI::init()
{

}
