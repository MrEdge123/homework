#ifndef FILEPROGRESSWINDOW_H
#define FILEPROGRESSWINDOW_H

#include <QWidget>

namespace Ui {
class FileProgressWindow;
}

class FileProgressWindow : public QWidget
{
    Q_OBJECT

public:
    FileProgressWindow(QWidget *parent = 0);
    ~FileProgressWindow();

    void setLabel(QString text);
    void setValue(int value);

private:
    Ui::FileProgressWindow *ui;
};

#endif // FILEPROGRESSWINDOW_H
