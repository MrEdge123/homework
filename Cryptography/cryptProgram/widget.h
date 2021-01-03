#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QStackedWidget>
#include "main_ui.h"
#include "des_ui.h"
#include "xor_ui.h"
#include "des_ui_sbox.h"
#include "des_ui_change.h"
#include "dh_ui.h"
#include "elgamal_ui.h"
#include "rsa_ui.h"
#include "short_en.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void changePage(QString str);

private:
    Ui::Widget *ui;

public:
    MAIN_UI *main_ui;
    DES_UI *des_ui;
    XOR_UI *xor_ui;
    des_ui_sbox *sbox_ui;
    DES_UI_CHANGE *des_ui_change;
    DH_UI *dh_ui;
    ELGAMAL_UI *elgamal_ui;
    RSA_UI *rsa_ui;
    SHORT_EN *short_en_ui;
};

#endif // WIDGET_H
