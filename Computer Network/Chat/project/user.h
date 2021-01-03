#ifndef USER_H
#define USER_H
#include <QString>
#include <QByteArray>
#include <QHostAddress>
#include "msghead.h"

const int UDP_PORT = 3000;
const int init_TCP_PORT = 3001;

class User
{
public:
    User();
    User(QString name, QHostAddress host);
    User(QByteArray msg);
    QByteArray toQByteArray();
    void addHead(QByteArray &msg);
    void removeHead(QByteArray &msg);

public:
    QString name;
    QHostAddress host;
    bool isOnline;
    int TCP_PORT_Msg;
    int TCP_PORT_File;

    bool operator == (User user) {
        return name == user.name && host == user.host && TCP_PORT_Msg == user.TCP_PORT_Msg;
    }

    bool operator != (User user) {
        return !(*this == user);
    }

};

#endif // USER_H
