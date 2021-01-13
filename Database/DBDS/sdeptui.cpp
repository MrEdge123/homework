#include "sdeptui.h"
#include "ui_sdeptui.h"

SdeptUI::SdeptUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SdeptUI)
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(query_sdept(int)));
    connect(ui->t3_no_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_t3_info_change(int)));
}

SdeptUI::~SdeptUI()
{
    delete ui;
}

void SdeptUI::init()
{
    ui->listWidget->clear();
    ui->t3_no_comboBox->clear();
    ui->t2_introduction_textEdit->setText("");
    ui->t2_name_lineEdit->setText("");
    ui->t2_no_lineEdit->setText("");

    QGridLayout *playout = new QGridLayout(this);

    QString sql = "select * from sdept ";

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        sdept_name_to_no.clear();
        sdept_no_to_name.clear();
        sdept_no_list.clear();

        while(ret.next()) {
            QString name = ret.value("no").toString() + " (" + ret.value("name").toString() + ")";
            QString no = ret.value("no").toString();

            QCheckBox *pbox = new QCheckBox(name, this);

            sdept_name_to_no.insert(name, no);
            sdept_no_to_name.insert(no, name);
            sdept_no_list.append(no);
            playout->addWidget(pbox);

            ui->listWidget->addItem(name);
        }
    }

    QLayoutItem *child;

    if(ui->t4_scrollAreaWidgetContents->layout()) {
        while( (child = ui->t4_scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
            if(child->widget()) {
                child->widget()->setParent(NULL);
            }
            delete child;
        }
        delete ui->t4_scrollAreaWidgetContents->layout();
    }

    ui->t4_scrollArea->widget()->setLayout(playout);

    foreach (QString no, sdept_no_list) {
        ui->t3_no_comboBox->addItem(no);
    }
}

void SdeptUI::query_sdept(int pos)
{
    if(pos < 0) return;

    QString sql =
            "select * from sdept "
            "where no = '%1' "
            ;

    sql = sql.arg(sdept_no_list[pos]);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        ret.next();

        QString no = ret.value("no").toString();
        QString name = ret.value("name").toString();
        QString introduction = ret.value("introduction").toString();

        ui->t1_no_lineEdit->setText(no);
        ui->t1_name_lineEdit->setText(name);
        ui->t1_introduction_textBrowser->setText(introduction);
    }
}

void SdeptUI::on_t2_add_pushButton_clicked()
{
    QString no = ui->t2_no_lineEdit->text();
    QString name = ui->t2_name_lineEdit->text();
    QString introduction = ui->t2_introduction_textEdit->toPlainText();

    if(no == "") {
        QMessageBox::critical(this, "错误", "系号为空");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "系名为空");
        return;
    }

    QString sql;
    QSqlQuery ret;

    sql =   "select no from sdept "
            "where no = '%1' "
            ;

    sql = sql.arg(no);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 1) {
            QMessageBox::critical(this, "错误", "系号已存在!");
            return;
        }
    }

    sql =
            "insert into sdept(no, name, introduction) "
            "values ('%1', '%2', '%3'); "
            ;

    sql = sql.arg(no, name, introduction);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        QMessageBox::information(this, "信息", "添加成功!");
        init();
    }
}

void SdeptUI::on_t3_info_change(int pos)
{
    if(pos < 0) return;

    QString sql =
            "select * from sdept "
            "where no = '%1' "
            ;

    sql = sql.arg(sdept_no_list[pos]);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        ret.next();

        QString name = ret.value("name").toString();
        QString introduction = ret.value("introduction").toString();

        ui->t3_name_lineEdit->setText(name);
        ui->t3_introduction_textEdit->setText(introduction);
    }
}

void SdeptUI::on_t3_m_pushButton_clicked()
{
    QString no = ui->t3_no_comboBox->currentText();
    QString name = ui->t3_name_lineEdit->text();
    QString introduction = ui->t3_introduction_textEdit->toPlainText();

    if(sdept_no_to_name.find(no) == sdept_no_to_name.end()) {
        QMessageBox::critical(this, "错误", "系号错误");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "系别为空");
        return;
    }

    QString sql;

    sql =   "update sdept "
            "set name = '%1', introduction = '%2' "
            "where no = '%3'; "
            ;

    sql = sql.arg(name, introduction, no);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        QMessageBox::information(this, "信息", "修改成功!");
    }
}

void SdeptUI::on_pushButton_clicked()
{
    if(QMessageBox::No == QMessageBox::warning(this, "警告", "确定要删除选定教职工?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No)) {
        return;
    }

    QLayout *layout = ui->t4_scrollAreaWidgetContents->layout();

    for(int i = 0; i < layout->count(); i++) {
        QLayoutItem *it = layout->itemAt(i);
        QCheckBox *pbox = qobject_cast<QCheckBox *>(it->widget());

        if(!pbox->isChecked()) continue;

        QString sql;

        sql =   "delete from sdept "
                "where no = '%1'; "
                ;

        sql = sql.arg(sdept_name_to_no[pbox->text()]);

        QSqlQuery ret;
        if(!ret.exec(sql)) {
            QMessageBox::critical(this, "错误", ret.lastError().text());
        }
        else {
            //succ
        }
    }

    init();
    QMessageBox::information(this, "信息", "删除完成!");
}
