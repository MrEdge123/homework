#ifndef TCUI_H
#define TCUI_H

#include <QWidget>

namespace Ui {
class TCUI;
}

class TCUI : public QWidget
{
    Q_OBJECT

public:
    explicit TCUI(QWidget *parent = 0);
    ~TCUI();

    void init();

private:
    Ui::TCUI *ui;
};

#endif // TCUI_H
