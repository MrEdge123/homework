#include "listwindow.h"
#include "ui_listwindow.h"
#include <QFile>

ListWindow::ListWindow(User user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWindow)
{
    ui->setupUi(this);
    myself = user;

    userList.append(User());
    items.append(NULL);
    cws.append(NULL);
    cntMsg.append(0);

    /* udp server */
    udpGet = new QUdpSocket();
    udpGet->bind(UDP_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpGet, SIGNAL(readyRead()), this, SLOT(getList()));

    /* tcp msg server */
    tcpServer_Msg = new QTcpServer();
    while(tcpServer_Msg->listen(QHostAddress::Any, myself.TCP_PORT_Msg) == false)
        myself.TCP_PORT_Msg++;
    connect(tcpServer_Msg, SIGNAL(newConnection()), this, SLOT(getConnection_Msg()));

    /* tcp file server */
    tcpServer_File = new QTcpServer();
    while(tcpServer_File->listen(QHostAddress::Any, myself.TCP_PORT_File) == false)
        myself.TCP_PORT_File++;
    connect(tcpServer_File, SIGNAL(newConnection()), this, SLOT(getConnection_File()));

    /* udp client */
    UdpSend* udpSend = new UdpSend(myself);
    udpSend->moveToThread(&udpSendThread);
    connect(&udpSendThread, &QThread::finished, udpSend, &QObject::deleteLater);
    connect(this, SIGNAL(online()), udpSend, SLOT(sendOnlineMsg()));
    udpSendThread.start();
    emit online();

    connect(ui->userList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(chatting(QListWidgetItem*)));

    ui->userName->setText(myself.name + " (" + myself.host.toString() + "::" + QString::number(myself.TCP_PORT_Msg) + ")");
}

ListWindow::~ListWindow()
{
    for(int i = 0; i < 20; i++) {
        QThread::currentThread()->msleep(50);
        UdpSend(myself).sendOfflineMsg();
    }
    foreach(ChatWindow* cw, cwsBuf) {
        delete cw;
    }
    delete udpGet;
    delete ui;
}

void ListWindow::getList()
{
    QByteArray msg;
    while(udpGet->hasPendingDatagrams()) {
        msg.resize(udpGet->pendingDatagramSize());
        udpGet->readDatagram(msg.data(), msg.size());
        User user(msg);
        if(myself != user && checkInList(user) == false && user.isOnline) {
            userList.append(user);
            QListWidgetItem* item = new QListWidgetItem(user.name + " (" + user.host.toString() + "::" + QString::number(user.TCP_PORT_Msg) + ")");
            items.append(item);
            ui->userList->addItem(item);
            cws.append(new ChatWindow(myself, user));
            cntMsg.append(0);

            //sendOnlineMsg();
        }
        if(checkInList(user) && user.isOnline == false) {
            int pos = findInList(user);

            cws[pos]->offlineMsg();

            userList.removeAt(pos);
            ui->userList->removeItemWidget(items[pos]);
            delete items[pos];
            items.removeAt(pos);
            cwsBuf.append(cws[pos]);
            cws.removeAt(pos);
            cntMsg.removeAt(pos);
        }
    }
}

void ListWindow::chatting(QListWidgetItem* item)
{
    int pos = -1;
    for(int i = 0; i < items.length(); i++) {
        if(items[i] == item) pos = i;
    }
    if(pos < 0) return;
    cws[pos]->show();
    cws[pos]->setWindowState(Qt::WindowActive);
    cws[pos]->activateWindow();
    displayCntMsg(pos, userList[pos]);
}

void ListWindow::getConnection_Msg()
{
    tcpGet_Msg = tcpServer_Msg->nextPendingConnection();
    connect(tcpGet_Msg, SIGNAL(readyRead()), this, SLOT(getMsg()));
}

void ListWindow::getConnection_File()
{
    tcpGet_File = tcpServer_File->nextPendingConnection();
    connect(tcpGet_File, SIGNAL(readyRead()), this, SLOT(getFile()));
}

bool ListWindow::checkInList(User user)
{
    foreach(User now, userList) {
        if(user == now) return true;
    }
    return false;
}

int ListWindow::findInList(User user)
{
    for(int i = 0; i < userList.length(); i++) {
        if(userList[i] == user) return i;
    }
    return -1;
}

void ListWindow::displayCntMsg(int pos, User user)
{
    if(cws[pos]->isHidden()) cntMsg[pos]++;
    else cntMsg[pos] = 0;

    QString text = user.name + " (" + user.host.toString() + "::" + QString::number(user.TCP_PORT_Msg) + ")";
    if(cntMsg[pos]) {
        text.append(" 未读(" + QString::number(cntMsg[pos]) + ")");
    }

    items[pos]->setText(text);
}

void ListWindow::getMsg()
{
    QByteArray msg = tcpGet_Msg->readAll();
    QByteArray t = msg;
    QString type = MsgHead::popHead(t);
    User user(t);
    int pos = findInList(user);
    if(type == QString("ChatMsg")) {
        cws[pos]->getMsg(msg);
        displayCntMsg(pos, user);
    }
    else if(type == QString("FileInfo")) {
        sendFileUserPos = pos;
        cws[pos]->getFileInfo(msg);
    }
    else if(type == QString("FileSendAllow")) {
        sendFileUserPos = pos;
        cws[pos]->startSendFile();
    }
    else if(type == QString("FileSendReject")) {
        cws[pos]->getFileRejectMsg();
    }
    else if(type == QString("sendFileACK")) {
        cws[sendFileUserPos]->isSendingFile = false;
        while(cws[sendFileUserPos]->sendFileFinished() == false) {
            QByteArray msg = tcpGet_File->readAll();
            if(msg.isEmpty()) break;
            cws[sendFileUserPos]->getFile(msg);
            qDebug() << "msg:" << msg << endl;
        }
    }

    tcpGet_Msg->close();
}

void ListWindow::getFile()
{
    QByteArray msg = tcpGet_File->readAll();
    cws[sendFileUserPos]->getFile(msg);
    if(cws[sendFileUserPos]->fileGetByte == cws[sendFileUserPos]->fileAllByte) {
        tcpGet_File->close();
    }
}

void ListWindow::closeEvent(QCloseEvent *e)
{
    //myself.isOnline = false;
    //sendOnlineMsg();
    qDebug() << "bye" << endl;
    udpSendThread.requestInterruption();
    udpSendThread.quit();
    udpSendThread.wait();

    e->accept();
}
