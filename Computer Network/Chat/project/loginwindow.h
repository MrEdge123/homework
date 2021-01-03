#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "listwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWindow *ui;
    ListWindow *lw;

    void keyPressEvent(QKeyEvent *e);
};

#endif // LOGINWINDOW_H
