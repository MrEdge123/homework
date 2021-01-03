#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    main_ui = new MAIN_UI(this);
    des_ui = new DES_UI(this);
    xor_ui = new XOR_UI(this);
    sbox_ui = new des_ui_sbox(this);
    des_ui_change = new DES_UI_CHANGE(this);
    dh_ui = new DH_UI(this);
    elgamal_ui = new ELGAMAL_UI(this);
    rsa_ui = new RSA_UI(this);
    short_en_ui = new SHORT_EN(this);

    ui->page->addWidget(main_ui);
    ui->page->addWidget(des_ui);
    ui->page->addWidget(xor_ui);
    ui->page->addWidget(sbox_ui);
    ui->page->addWidget(des_ui_change);
    ui->page->addWidget(dh_ui);
    ui->page->addWidget(elgamal_ui);
    ui->page->addWidget(rsa_ui);
    ui->page->addWidget(short_en_ui);

    ui->page->setCurrentWidget(main_ui);

    connect(main_ui, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));
    connect(des_ui, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));
    connect(xor_ui, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));
    connect(sbox_ui, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));
    connect(des_ui_change, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));
    connect(dh_ui, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));
    connect(elgamal_ui, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));
    connect(rsa_ui, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));
    connect(short_en_ui, SIGNAL(back_signal(QString)), this, SLOT(changePage(QString)));

    this->setFixedSize(800, 600);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changePage(QString str)
{
    if(str == "main") {
        ui->page->setCurrentWidget(main_ui);
        this->setFixedSize(850, 600);
    }
    else if(str == "des") {
        ui->page->setCurrentWidget(des_ui);
        this->setFixedSize(850, 270);
    }
    else if(str == "xor") {
        ui->page->setCurrentWidget(xor_ui);
        this->setFixedSize(850, 270);
    }
    else if(str == "des_sbox") {
        ui->page->setCurrentWidget(sbox_ui);
        this->setFixedSize(850, 600);
    }
    else if(str == "des_change") {
        ui->page->setCurrentWidget(des_ui_change);
        this->setFixedSize(850, 600);
    }
    else if(str == "dh") {
        ui->page->setCurrentWidget(dh_ui);
        //this->setFixedSize(850, 600);
    }
    else if(str == "elgamal") {
        ui->page->setCurrentWidget(elgamal_ui);
        //this->setFixedSize(850, 600);
    }
    else if(str == "rsa") {
        ui->page->setCurrentWidget(rsa_ui);
        //this->setFixedSize(850, 600);
    }
    else if(str == "short_en") {
        ui->page->setCurrentWidget(short_en_ui);
        this->setFixedSize(850, 500);
    }
}
