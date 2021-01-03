#ifndef FILESENDWINDOW_H
#define FILESENDWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QCloseEvent>

namespace Ui {
class FileSendWindow;
}

class FileSendWindow : public QWidget
{
    Q_OBJECT

signals:
    void accept();

public:
    FileSendWindow(QWidget *parent = 0);
    ~FileSendWindow();

    void setLabel(QString text);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FileSendWindow *ui;
};

#endif // FILESENDWINDOW_H
