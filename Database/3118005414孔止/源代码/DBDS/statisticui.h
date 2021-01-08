#ifndef STATISTICUI_H
#define STATISTICUI_H

#include <QWidget>

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

private:
    Ui::StatisticUI *ui;
};

#endif // STATISTICUI_H
