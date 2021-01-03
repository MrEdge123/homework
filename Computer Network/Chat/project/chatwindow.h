#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTime>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <QThread>
#include <QKeyEvent>
#include "user.h"
#include "filegetwindow.h"
#include "filesendwindow.h"
#include "fileprogresswindow.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

signals:

public:
    ChatWindow(User myself, User user, QWidget *parent = 0);
    ~ChatWindow();

private slots:
    void on_closeButton_clicked();
    void connectToUser_Msg();
    void connectToUser_File();
    void sendMsg();
    void sendFile();
    void readySendFileACK();
    void sendFileACK();
    void readySendFileInfo();
    void sendFileInfo();
    void readySendFileAllow(QString saveDir);
    void sendFileAllow();
    void readySendFileReject();
    void sendFileReject();
    void sendFileProcess();

    void on_pushButton_clicked();

private:
    Ui::ChatWindow *ui;
    User user;
    User myself;
    QTcpSocket* tcpSend_Msg;
    QTcpSocket* tcpSend_File;

    FileSendWindow* fileSendWindow;
    FileGetWindow* fileGetWindow;
    FileProgressWindow* fileProgressWindow;

    QFile *file;
    QString filePath;
    QString fileName;
    QString fileDir;
    QByteArray fileByteArray;
    long long fileSendByte;
    long long fileGetByte;
    long long fileAllByte;

    QString getFileName(QString filePath);

    void keyPressEvent(QKeyEvent *e);

public:
    void getMsg(QByteArray msg);
    void getFile(QByteArray msg);
    void offlineMsg();
    void getFileInfo(QByteArray msg);
    void getFileRejectMsg();
    void startSendFile();
    bool sendFileFinished();
    void changePlainToHtml(QString &text);
    static const long long fileBlockByte = 100;

    bool isSendingFile;
};

#endif // CHATWINDOW_H
