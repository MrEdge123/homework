#include "des_ui_change.h"
#include "ui_des_ui_change.h"

DES_UI_CHANGE::DES_UI_CHANGE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DES_UI_CHANGE)
{
    ui->setupUi(this);

    QRegExp regx("[1-9][0-9]*");
    QValidator *validator = new QRegExpValidator(regx, this);

    ui->runCnt_lineEdit->setValidator(validator);
}

DES_UI_CHANGE::~DES_UI_CHANGE()
{
    delete ui;
}

void DES_UI_CHANGE::on_back_button_clicked()
{
    emit back_signal("main");
}

void DES_UI_CHANGE::on_mode_button_clicked()
{
    emit back_signal("des");
}

void DES_UI_CHANGE::on_run_button_clicked()
{
    if(ui->runCnt_radioButton->isChecked()) {
        runCnt = ui->runCnt_lineEdit->text().toInt(NULL, 10);
    }

    //ui->textBrowser->setText("runCnt:" + QString::number(runCnt));

    if(runCnt == 0 || runCnt > 1000) {
        QMessageBox::critical(this, "错误", "次数太多了!");
        return;
    }

    int ans[65];
    for(int i = 1; i <= 64; i++) ans[i] = 0;

    ui->textBrowser->setText("运行中...");

    QString text;

    //run
    int T = runCnt;
    while(T--) {
        ULL msg = CLIB::generate_bit(64);
        ULL key = CLIB::generate_bit(64);

        DES des = DES();
        ULL cpt = des.run(msg, key);

        for(int i = 1; i <= 64; i++) {
            ULL change;
            if(const_status) change = msg;
            else change = key;

            //change
            std::vector<int> bit = CLIB::select_random_num(64, i);
            for(int it : bit) {
                change = CLIB::change_bit(change, it - 1);
            }

            if(const_status) {
                //if(i == 1) qDebug() << "change:" + QString::number(change, 2) + "\n";
                //if(i == 1) qDebug() << "mmmmsg:" + QString::number(msg, 2) + "\n";
            }
            else {
                //if(i == 1) qDebug() << "change:" + QString::number(change, 2) + "\n";
                //if(i == 1) qDebug() << "kkkkey:" + QString::number(key, 2) + "\n";
            }

            ULL out;
            if(const_status) out = des.run(change, key);
            else out = des.run(msg, change);

            ans[i] += CLIB::cmp_bit(cpt, out);
        }
    }


    text += "变化情况:\n\n";

    int sum = 0;
    for(int i = 1; i <= 64; i++) {
        sum += ans[i];
    }

    text += "平均变化: " + QString::number((double)sum / runCnt / 64) + "位\n\n";

    for(int i = 1; i <= 64; i++) {
        text += "改变" + QString::number(i) + "位, 密文变化: ";
        text += QString::number((double)ans[i] / runCnt) + "位\n\n";
    }

    ui->textBrowser->setText(text);
}

void DES_UI_CHANGE::on_constKey_button_clicked()
{
    const_status = 1;
}

void DES_UI_CHANGE::on_constMsg_button_clicked()
{
    const_status = 0;
}

void DES_UI_CHANGE::on_runCnt_radioButton_clicked()
{
    ui->runCnt_lineEdit->setEnabled(true);
}

void DES_UI_CHANGE::on_runCnt1_radioButton_clicked()
{
    ui->runCnt_lineEdit->setEnabled(false);
    runCnt = 1;
}

void DES_UI_CHANGE::on_runCnt10_radioButton_clicked()
{
    ui->runCnt_lineEdit->setEnabled(false);
    runCnt = 10;
}

void DES_UI_CHANGE::on_runCnt100_radioButton_clicked()
{
    ui->runCnt_lineEdit->setEnabled(false);
    runCnt = 100;
}
