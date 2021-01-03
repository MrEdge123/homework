#ifndef DES_UI_H
#define DES_UI_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include "des.h"
#include "clib.h"

namespace Ui {
class DES_UI;
}

class DES_UI : public QWidget
{
    Q_OBJECT

signals:
    void back_signal(QString str);

public:
    explicit DES_UI(QWidget *parent = 0);
    ~DES_UI();

private slots:
    void on_back_button_clicked();

    void on_genMsg_button_clicked();

    void on_genKey_button_clicked();

    void on_encrypt_button_clicked();

    void on_decrypt_button_clicked();

    void on_mode_button_clicked();

private:
    Ui::DES_UI *ui;
};

#endif // DES_UI_H
