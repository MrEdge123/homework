#include "loginwindow.h"
#include "listwindow.h"
#include "ui_loginwindow.h"
#include "user.h"
#include <QNetworkInterface>
#include <QFile>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete lw;
}

void LoginWindow::on_loginButton_clicked()
{
    this->hide();

    QList<QHostAddress> hosts = QNetworkInterface::allAddresses();
    QHostAddress host;
    quint32 minAddr = QHostAddress("192.168.0.0").toIPv4Address();
    quint32 maxAddr = QHostAddress("192.168.255.255").toIPv4Address();
    foreach(QHostAddress addr, hosts) {
        if(addr.protocol() == QAbstractSocket::IPv4Protocol)
            if(addr.toIPv4Address() >= minAddr && addr.toIPv4Address() <= maxAddr)
                host = addr;
    }
    User user(ui->userEdit->text(), host);

    lw = new ListWindow(user);

    lw->show();
}

void LoginWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        on_loginButton_clicked();
    }
}
