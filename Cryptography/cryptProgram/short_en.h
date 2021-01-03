#ifndef SHORT_EN_H
#define SHORT_EN_H

#include <QWidget>
#include "des.h"

namespace Ui {
class SHORT_EN;
}

class SHORT_EN : public QWidget
{
    Q_OBJECT

signals:
    void back_signal(QString str);

public:
    explicit SHORT_EN(QWidget *parent = 0);
    ~SHORT_EN();

private slots:
    void on_back_button_clicked();

    void on_srcFilePath_button_clicked();

    void on_dstFilePath_button_clicked();

    void on_mode1_radioButton_clicked();

    void on_mode2_radioButton_clicked();

    void on_mode3_radioButton_clicked();

    void on_genKey_button_clicked();

    void on_encrypt_button_clicked();

    void on_decrypt_button_clicked();

private:
    Ui::SHORT_EN *ui;
    int mode = 1;

    void crypt(bool isEncrypt);
};

#endif // SHORT_EN_H
