#ifndef SENDFILEWINDOW_H
#define SENDFILEWINDOW_H

#include <QDialog>

namespace Ui {
class SendFileWindow;
}

class SendFileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SendFileWindow(QWidget *parent = 0);
    ~SendFileWindow();

private:
    Ui::SendFileWindow *ui;
};

#endif // SENDFILEWINDOW_H
