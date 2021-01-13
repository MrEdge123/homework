#ifndef STATISTICUI_H
#define STATISTICUI_H

#include <QWidget>
#include "header.h"

namespace Ui {
class StatisticUI;
}

class StatisticUI : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticUI(QWidget *parent = 0);
    ~StatisticUI();

    void init();

private slots:
    void on_radioButton_pressed();

private:
    Ui::StatisticUI *ui;
};

#endif // STATISTICUI_H
