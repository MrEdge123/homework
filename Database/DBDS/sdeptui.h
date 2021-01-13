#ifndef SDEPTUI_H
#define SDEPTUI_H

#include <QWidget>
#include "header.h"

namespace Ui {
class SdeptUI;
}

class SdeptUI : public QWidget
{
    Q_OBJECT

public:
    explicit SdeptUI(QWidget *parent = 0);
    ~SdeptUI();

    void init();

private slots:
    void query_sdept(int pos);

    void on_t2_add_pushButton_clicked();

    void on_t3_info_change(int pos);

    void on_t3_m_pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::SdeptUI *ui;

    QMap<QString, QString> sdept_name_to_no;
    QMap<QString, QString> sdept_no_to_name;

    QList<QString> sdept_no_list;
};

#endif // SDEPTUI_H
