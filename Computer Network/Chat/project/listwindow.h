#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QList>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "user.h"
#include "chatwindow.h"
#include "udpsend.h"

namespace Ui {
class ListWindow;
}

class ListWindow : public QWidget
{
    Q_OBJECT

public:
    ListWindow(User user, QWidget *parent = 0);
    ~ListWindow();

private:
    Ui::ListWindow *ui;

    QList<User> userList;
    QList<QListWidgetItem*> items;
    QList<ChatWindow*> cws;
    QList<ChatWindow*> cwsBuf;
    QList<int> cntMsg;

    User myself;

    QUdpSocket *udpGet;
    QThread udpSendThread;

    QTcpServer *tcpServer_Msg;
    QTcpSocket *tcpGet_Msg;

    QTcpServer *tcpServer_File;
    QTcpSocket *tcpGet_File;

    int sendFileUserPos;

signals:
    void online();
    void offline();

private slots:
    void getList();
    void chatting(QListWidgetItem* item);
    void getConnection_Msg();
    void getConnection_File();
    void getMsg();
    void getFile();

private:
    bool checkInList(User user);
    int findInList(User user);
    void displayCntMsg(int pos, User user);

    void closeEvent(QCloseEvent *e);
};

#endif // LISTWINDOW_H
