#ifndef UDPSEND_H
#define UDPSEND_H

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include "user.h"

class UdpSend : public QObject
{
    Q_OBJECT
public:
    UdpSend(User user, QObject *parent = nullptr);

signals:

public slots:
    void sendOnlineMsg();
    void sendOfflineMsg();

private:
    User user;
    QUdpSocket* udpSend;
};

#endif // UDPSEND_H
