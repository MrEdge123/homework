#ifndef COURSEUI_H
#define COURSEUI_H

#include <QWidget>

namespace Ui {
class CourseUI;
}

class CourseUI : public QWidget
{
    Q_OBJECT

public:
    explicit CourseUI(QWidget *parent = 0);
    ~CourseUI();

    void init();

private:
    Ui::CourseUI *ui;
};

#endif // COURSEUI_H
