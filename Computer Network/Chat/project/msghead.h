#ifndef MSGHEAD_H
#define MSGHEAD_H

#include <QByteArray>
#include <QString>

class MsgHead {

public:

    MsgHead() {}

    static void removeHead(QByteArray& msg) {
        QByteArray ans;
        int pos = 0;
        while(pos < msg.length() && msg[pos] != '\n') pos++;
        pos++;

        while(pos < msg.length()) ans.append(msg[pos++]);
        msg = ans;
    }

    static void addHead(QByteArray& msg, QString head) {
        msg.prepend(QString(head + "\n").toUtf8());
    }

    static QString getHead(QByteArray msg) {
        QByteArray t;
        int pos = 0;
        while(pos < msg.length() && msg[pos] != '\n') t.append(msg[pos++]);
        return QString(t);
    }

    static QString popHead(QByteArray &msg) {
        QString ans = getHead(msg);
        removeHead(msg);
        return ans;
    }

};

#endif // MSGHEAD_H
