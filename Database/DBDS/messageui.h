#ifndef MESSAGEUI_H
#define MESSAGEUI_H

#include <QWidget>
#include "header.h"

namespace Ui {
class MessageUI;
}

class MessageUI : public QWidget
{
    Q_OBJECT

public:
    explicit MessageUI(QWidget *parent = 0);
    ~MessageUI();

    void init();

private:
    Ui::MessageUI *ui;
};

#endif // MESSAGEUI_H
