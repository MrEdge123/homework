#ifndef SCOREUI_H
#define SCOREUI_H

#include <QWidget>
#include "header.h"

namespace Ui {
class ScoreUI;
}

class ScoreUI : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreUI(QWidget *parent = 0);
    ~ScoreUI();

    void init();

private:
    Ui::ScoreUI *ui;
};

#endif // SCOREUI_H
