#include "user.h"

User::User()
{

}

User::User(QString name, QHostAddress host)
{
    this->name = name;
    this->host = host;
    isOnline = true;
    TCP_PORT_Msg = init_TCP_PORT;
    TCP_PORT_File = TCP_PORT_Msg + 1;
}

User::User(QByteArray msg)
{
    QString state = MsgHead::popHead(msg);
    if(state == QString("online")) isOnline = true;
    else isOnline = false;

    name = MsgHead::popHead(msg);
    host = QHostAddress(MsgHead::popHead(msg));

    TCP_PORT_Msg = MsgHead::popHead(msg).toInt();
    TCP_PORT_File = MsgHead::popHead(msg).toInt();
}

QByteArray User::toQByteArray()
{
    QString msg;

    if(isOnline) msg.append("online\n");
    else msg.append("offline\n");

    msg.append(name + "\n");
    msg.append(host.toString() + "\n");
    msg.append(QString::number(TCP_PORT_Msg) + "\n");
    msg.append(QString::number(TCP_PORT_File) + "\n");

    return msg.toUtf8();
}

void User::addHead(QByteArray& msg)
{
    msg.prepend(toQByteArray());
}

void User::removeHead(QByteArray& msg)
{
    for(int i = 1; i <= 5; i++) {
        MsgHead::removeHead(msg);
    }
}

