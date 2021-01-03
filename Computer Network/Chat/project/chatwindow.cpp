#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(User myself, User user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    this->myself = myself;
    this->user = user;
    this->setWindowTitle(user.name);

    file = NULL;
    isSendingFile = false;
    fileSendWindow = new FileSendWindow();
    fileGetWindow = new FileGetWindow();
    fileProgressWindow = new FileProgressWindow();

    setFocusPolicy(Qt::StrongFocus);

    connect(ui->sendButton, SIGNAL(clicked(bool)), this, SLOT(connectToUser_Msg()));

    tcpSend_File = new QTcpSocket();
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_closeButton_clicked()
{
    this->close();
}

void ChatWindow::connectToUser_Msg()
{
    QString text = ui->inText->toPlainText();
    if(text != "") {
        tcpSend_Msg = new QTcpSocket();
        tcpSend_Msg->connectToHost(user.host, user.TCP_PORT_Msg);
        connect(tcpSend_Msg, SIGNAL(connected()), this, SLOT(sendMsg()));
    }
}

void ChatWindow::connectToUser_File()
{
    tcpSend_File->connectToHost(user.host, user.TCP_PORT_File);
    connect(tcpSend_File, SIGNAL(connected()), this, SLOT(sendFile()));
}

void ChatWindow::getMsg(QByteArray msg)
{
    QString type = MsgHead::popHead(msg);
    QString head;
    if(type == QString("ChatMsg")) qDebug() << "ChatMsg" << endl;
    user.removeHead(msg);
    QString text = msg;
    if(text != "") {

        //changePlainToHtml(text);

        //text.prepend("<p>");
        //text.append("</p>");

        head =  user.name + " (" + user.host.toString() + "::" +
                QString::number(user.TCP_PORT_Msg) + ") " +
                QTime::currentTime().toString("hh:mm");

        head.prepend("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\"><span style=\" color:blue;\">");
        head.append("</span></p>");

        text.prepend(head);

        ui->outText->append(text);
    }
}

void ChatWindow::getFile(QByteArray msg)
{
    if(msg.isEmpty()) return;
    fileByteArray.append(msg);
    fileGetByte += msg.size();
    if(fileGetByte == fileAllByte) {
        file->write(fileByteArray);
        file->close();
        fileProgressWindow->setValue(100);
        return;
    }
    else if(fileGetByte > fileAllByte) {
        qDebug() << endl;
        qDebug() << "send file failed!" << endl;
        return;
    }

    int value = (double)fileGetByte / fileAllByte * 100;
    fileProgressWindow->setValue(value);
}

void ChatWindow::offlineMsg()
{
    ui->outText->append("<br><p style=\"color:red\">系统消息: 对方已离线!</p>");
    ui->inText->setReadOnly(true);
    ui->sendButton->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

void ChatWindow::sendMsg()
{
    qDebug() << "send chat msg" << endl;
    QString text = ui->inText->toHtml();
    QString head;
    if(text != "") {
        QByteArray msg;
        msg.append(text);
        myself.addHead(msg);
        MsgHead::addHead(msg, "ChatMsg");
        tcpSend_Msg->write(msg);
        ui->inText->clear();

        //changePlainToHtml(text);

        head =  myself.name + " (" + myself.host.toString() + "::" +
                QString::number(myself.TCP_PORT_Msg) + ") " +
                QTime::currentTime().toString("hh:mm");

        head.prepend("<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\"><span style=\" color:green;\">");
        head.append("</span></p>");

        text.prepend(head);

        ui->outText->append(text);

        qDebug() << ui->outText->toHtml() << endl << endl;
    }
}

void ChatWindow::sendFile()
{
    QByteArray msg;
    int pos = fileSendByte;
    fileSendByte += fileBlockByte;
    while(pos < fileSendByte && pos < fileAllByte) {
        msg.append(fileByteArray[pos++]);
    }
    //qDebug() << "sendFileStream:" << msg << endl << endl;
    tcpSend_File->write(msg);

    int value;
    if(fileSendByte >= fileAllByte) value = 100;
    else value = (double)fileSendByte / fileAllByte * 100;

    fileProgressWindow->setValue(value);
}

void ChatWindow::readySendFileACK()
{
    tcpSend_Msg = new QTcpSocket();
    tcpSend_Msg->connectToHost(user.host, user.TCP_PORT_Msg);
    connect(tcpSend_Msg, SIGNAL(connected()), this, SLOT(sendFileACK()));
}

void ChatWindow::sendFileACK()
{
    qDebug() << "send file ack" << endl;
    QByteArray msg;
    myself.addHead(msg);
    MsgHead::addHead(msg, "sendFileACK");
    tcpSend_Msg->write(msg);
}

void ChatWindow::readySendFileInfo()
{
    tcpSend_Msg = new QTcpSocket();
    tcpSend_Msg->connectToHost(user.host, user.TCP_PORT_Msg);
    connect(tcpSend_Msg, SIGNAL(connected()), this, SLOT(sendFileInfo()));
}

void ChatWindow::sendFileInfo()
{
    qDebug() << "send file info" << endl;
    QByteArray msg;
    msg.append(fileName + "\n");
    msg.append(QString::number(fileAllByte) + "\n");
    myself.addHead(msg);
    MsgHead::addHead(msg, "FileInfo");

    tcpSend_Msg->write(msg);
}

void ChatWindow::readySendFileAllow(QString saveDir)
{
    fileDir = saveDir;
    qDebug() << "fileSaveDir" << fileDir << endl;

    filePath = fileDir + "/" + fileName;

    QFileInfo info(filePath);
    if(info.isFile()) {
        if(isSendingFile == false)
            QMessageBox::critical(this, tr("Warning"), "该目录存在同名文件, 请重新选择目录!");
        return;
    }

    file = new QFile(filePath);
    file->open(QFile::WriteOnly);

    fileGetWindow->hide();

    fileProgressWindow->show();
    fileProgressWindow->setWindowState(Qt::WindowActive);
    fileProgressWindow->activateWindow();
    fileProgressWindow->setWindowTitle("接收文件");
    fileProgressWindow->setLabel("文件名: " + fileName);
    fileProgressWindow->setValue(0);
    isSendingFile = true;
    fileByteArray = QByteArray();

    tcpSend_Msg = new QTcpSocket();
    tcpSend_Msg->connectToHost(user.host, user.TCP_PORT_Msg);
    connect(tcpSend_Msg, SIGNAL(connected()), this, SLOT(sendFileAllow()));
}

void ChatWindow::sendFileAllow()
{
    qDebug() << "send file allow" << endl;
    QByteArray msg;
    myself.addHead(msg);
    MsgHead::addHead(msg, "FileSendAllow");

    tcpSend_Msg->write(msg);
}

void ChatWindow::readySendFileReject()
{
    tcpSend_Msg = new QTcpSocket();
    tcpSend_Msg->connectToHost(user.host, user.TCP_PORT_Msg);
    connect(tcpSend_Msg, SIGNAL(connected()), this, SLOT(sendFileReject()));
}

void ChatWindow::sendFileReject()
{
    qDebug() << "send file reject" << endl;
    QByteArray msg;
    myself.addHead(msg);
    MsgHead::addHead(msg, "FileSendReject");

    tcpSend_Msg->write(msg);
}

void ChatWindow::getFileInfo(QByteArray msg)
{
    if(isSendingFile) {
        readySendFileReject();
        return;
    }

    MsgHead::removeHead(msg);
    myself.removeHead(msg);

    fileName = MsgHead::popHead(msg);
    fileAllByte = MsgHead::popHead(msg).toInt();
    fileGetByte = 0;

    fileGetWindow->setWindowFlags(Qt::WindowStaysOnTopHint);
    fileGetWindow->show();
    fileGetWindow->setWindowState(Qt::WindowActive);
    fileGetWindow->activateWindow();
    QString text = "是否接收来自" + user.name + "的文件: " + fileName + "?";
    text.append(" 大小: " + QString::number(fileAllByte / 1024) + "KB");
    fileGetWindow->setLabel(text);
    connect(fileGetWindow, SIGNAL(accept(QString)), this, SLOT(readySendFileAllow(QString)));
    connect(fileGetWindow, SIGNAL(reject()), this, SLOT(readySendFileReject()));
}

void ChatWindow::getFileRejectMsg()
{
    fileSendWindow->hide();
    QMessageBox::critical(this, tr("Warning"), "对方拒绝接受文件!");
}

void ChatWindow::startSendFile()
{
    fileSendWindow->hide();
    fileProgressWindow->show();
    fileProgressWindow->setWindowState(Qt::WindowActive);
    fileProgressWindow->activateWindow();
    fileProgressWindow->setWindowTitle("发送文件");
    fileProgressWindow->setLabel("文件名: " + fileName);
    fileProgressWindow->setValue(0);
    isSendingFile = true;

    sendFileProcess();
    connect(tcpSend_File, SIGNAL(disconnected()), this, SLOT(sendFileProcess()));
}

bool ChatWindow::sendFileFinished()
{
    if(fileGetByte == fileAllByte) return true;
    return false;
}

void ChatWindow::changePlainToHtml(QString &text)
{
    text.replace(">", "&gt;");
    text.replace("<", "&lt;");
    text.replace("\"", "&quot;");
    text.replace("\'", "&#39;");
    text.replace(" ", "&nbsp;");
    text.replace("\n", "<br>");
}

void ChatWindow::sendFileProcess()
{
    if(fileSendByte >= fileAllByte) {
        isSendingFile = false;
        readySendFileACK();
        return;
    }
    connectToUser_File();
}

void ChatWindow::on_pushButton_clicked()
{
    if(isSendingFile) {
        QMessageBox::critical(this, tr("Warning"), "请等待其他文件发送完毕!");
        return;
    }

    filePath = QFileDialog::getOpenFileName(this);
    if(filePath.isEmpty()) {
        return;
    }

    fileName = getFileName(filePath);

    qDebug() << "filePath:" << filePath;
    qDebug() << "fileName:" << fileName;
    qDebug() << endl;

    if(file != NULL) delete file;
    file = new QFile(filePath);
    bool ok = file->open(QFile::ReadOnly);
    if(ok == false) {
        QMessageBox::critical(this,tr("Warning"),"文件不能打开!");
        return;
    }
    fileByteArray = file->readAll();
    fileAllByte = fileByteArray.length();

    if(fileAllByte > 10 * 1024 * 1024) {
        QMessageBox::critical(this,tr("Warning"),"传输文件太大!");
        return;
    }

    fileSendByte = 0;

    qDebug() << "fileAllByte:" << fileAllByte << endl;

    fileSendWindow->show();
    fileSendWindow->setWindowState(Qt::WindowActive);
    fileSendWindow->activateWindow();
    QString text = "确定要发送文件: " + fileName + "?";
    text.append(" 大小: " + QString::number(fileAllByte / 1024) + "KB");
    fileSendWindow->setLabel(text);
    connect(fileSendWindow, SIGNAL(accept()), this, SLOT(readySendFileInfo()));
}

QString ChatWindow::getFileName(QString filePath)
{
    int pos = 0;
    for(int i = 0; i < filePath.length(); i++) {
        if(filePath[i] == '/') pos = i;
    }
    pos++;

    QString ans;
    while(pos < filePath.length()) ans.append(filePath[pos++]);

    return ans;
}

void ChatWindow::keyPressEvent(QKeyEvent *e)
{
    if((e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_Return)) {
        emit ui->sendButton->clicked();
    }
}
