#include "udpsend.h"

UdpSend::UdpSend(User user, QObject *parent) : QObject(parent)
{
    this->user = user;
    udpSend = new QUdpSocket();
}

void UdpSend::sendOnlineMsg()
{
    while(true) {
        QThread::currentThread()->msleep(200);
        user.isOnline = true;
        QByteArray msg = user.toQByteArray();
        udpSend->writeDatagram(msg, QHostAddress::Broadcast, UDP_PORT);
        if(QThread::currentThread()->isInterruptionRequested()) break;
    }
}

void UdpSend::sendOfflineMsg()
{
    user.isOnline = false;
    QByteArray msg = user.toQByteArray();
    udpSend->writeDatagram(msg, QHostAddress::Broadcast, UDP_PORT);
}
