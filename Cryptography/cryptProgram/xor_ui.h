#ifndef XOR_UI_H
#define XOR_UI_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QByteArray>
#include "clib.h"
#include "xor.h"

namespace Ui {
class XOR_UI;
}

class XOR_UI : public QWidget
{
    Q_OBJECT

public:
    explicit XOR_UI(QWidget *parent = 0);
    ~XOR_UI();

signals:
    void back_signal(QString str);

private slots:
    void on_back_button_clicked();

    void on_srcFilePath_button_clicked();

    void on_dstFilePath_button_clicked();

    void on_genKey_button_clicked();

    void on_encrypt_button_clicked();

private:
    Ui::XOR_UI *ui;
};

#endif // XOR_UI_H
