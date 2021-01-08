#ifndef WELCOMEUI_H
#define WELCOMEUI_H

#include <QWidget>

namespace Ui {
class WelcomeUI;
}

class WelcomeUI : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeUI(QWidget *parent = 0);
    ~WelcomeUI();

private:
    Ui::WelcomeUI *ui;
};

#endif // WELCOMEUI_H
