#ifndef FILEGETWINDOW_H
#define FILEGETWINDOW_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class FileGetWindow;
}

class FileGetWindow : public QWidget
{
    Q_OBJECT

signals:
    void accept(QString filePath);
    void reject();

public:
    FileGetWindow(QWidget *parent = 0);
    ~FileGetWindow();

    void setLabel(QString text);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FileGetWindow *ui;
};

#endif // FILEGETWINDOW_H
