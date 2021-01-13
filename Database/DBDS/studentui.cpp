#include "studentui.h"
#include "ui_studentui.h"

StudentUI::StudentUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentUI)
{
    ui->setupUi(this);
}

StudentUI::~StudentUI()
{
    delete ui;
}

void StudentUI::init()
{
    //ui
    ui->t1_birth_dateEdit->setTime(QTime::currentTime());
    ui->t1_name_lineEdit->setText("");
    ui->t1_no_lineEdit->setText("");
    ui->t1_score_lineEdit->setText("");
    ui->t1_sdept_comboBox->clear();
    ui->t1_sex_comboBox->setCurrentIndex(0);

    ui->t2_birth_dateEdit->setTime(QTime::currentTime());
    ui->t2_name_lineEdit->setText("");
    ui->t2_no_lineEdit->setText("");
    ui->t2_q_no_lineEdit->setText("");
    ui->t2_score_lineEdit->setText("");
    ui->t2_sex_comboBox->setCurrentIndex(0);

    ui->t2_birth_dateEdit->setEnabled(false);
    ui->t2_m_pushButton->setEnabled(false);
    ui->t2_name_lineEdit->setEnabled(false);
    ui->t2_score_lineEdit->setEnabled(false);
    ui->t2_sdept_comboBox->setEnabled(false);
    ui->t2_sex_comboBox->setEnabled(false);

    //sdept
    QString sql = "select * from sdept";

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        sdept_name_to_no.clear();
        sdept_no_to_name.clear();

        while(ret.next()) {
            QString name = ret.value("no").toString() + " (" + ret.value("name").toString() + ")";
            QString no = ret.value("no").toString();

            sdept_name_to_no.insert(name, no);
            sdept_no_to_name.insert(no, name);

            ui->t1_sdept_comboBox->addItem(name);
            ui->t2_sdept_comboBox->addItem(name);
        }
    }

    //student
    QGridLayout *playout = new QGridLayout(this);
    sql = "select no, name from student ";
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        student_name_to_no.clear();

        while(ret.next()) {
            QString name = ret.value("no").toString() + " (" + ret.value("name").toString() + ")";
            QString no = ret.value("no").toString();

            QCheckBox *pbox = new QCheckBox(name, this);

            student_name_to_no.insert(name, no);
            playout->addWidget(pbox);
        }
    }

    QLayoutItem *child;

    if(ui->t3_scrollAreaWidgetContents->layout()) {
        while( (child = ui->t3_scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
            if(child->widget()) {
                child->widget()->setParent(NULL);
            }
            delete child;
        }
        delete ui->t3_scrollAreaWidgetContents->layout();
    }

    ui->t3_scrollArea->widget()->setLayout(playout);
}

void StudentUI::on_t1_add_pushButton_clicked()
{
    QString no = ui->t1_no_lineEdit->text();
    QString name = ui->t1_name_lineEdit->text();
    QString sex = ui->t1_sex_comboBox->currentText();
    QString birth = ui->t1_birth_dateEdit->text();
    QString ad_score = ui->t1_score_lineEdit->text();
    QString sdept_no;

    if(no == "") {
        QMessageBox::critical(this, "错误", "学号为空");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "姓名为空");
        return;
    }

    if(sdept_name_to_no.find(ui->t1_sdept_comboBox->currentText())
            == sdept_name_to_no.end()) {
        QMessageBox::critical(this, "错误", "系别输入错误");
        return;
    }

    if(ad_score == "") {
        QMessageBox::critical(this, "错误", "入学成绩未输入!");
        return;
    }

    sdept_no = sdept_name_to_no[ui->t1_sdept_comboBox->currentText()];

    QString sql =
            "select * from user "
            "where no = '%1' "
            ;

    sql = sql.arg(no);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 1) {
            QMessageBox::critical(this, "错误", "用户号已存在!");
            return;
        }
    }

    sql =
            "insert into user(no, password, identity) "
            "values ('%1', '%2', '%3'); "
            ;

    sql = sql.arg(no, "123456", "学生");

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        sql = "insert into student(no, name, sex, birth, ad_score, sdept_no) "
              "values ('%1', '%2', '%3', '%4', %5, '%6'); "
                ;

        sql = sql.arg(no, name, sex, birth, ad_score, sdept_no);

        if(!ret.exec(sql)) {
            QMessageBox::critical(this, "错误", ret.lastError().text());
        }
        else {
            QMessageBox::information(this, "信息", "添加成功!");
            init();
        }
    }
}

void StudentUI::on_t2_q_pushButton_clicked()
{
    QString no = ui->t2_q_no_lineEdit->text();

    QString sql =
            "select * from student "
            "where no = '%1'; "
            ;

    sql = sql.arg(no);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 0) {
            QMessageBox::critical(this, "错误", "用户号不存在!");
        }
        else {
            ret.next();
            ui->t2_no_lineEdit->setText(no);

            QString time = ret.value("birth").toString();
            QString name = ret.value("name").toString();
            QString sex = ret.value("sex").toString();
            QString score = ret.value("ad_score").toString();
            QString sdept_no = ret.value("sdept_no").toString();

            //qDebug() << time;
            //qDebug() << QDate::fromString(time, "yyyy-MM-dd");

            ui->t2_birth_dateEdit->setEnabled(true);
            ui->t2_m_pushButton->setEnabled(true);
            ui->t2_name_lineEdit->setEnabled(true);
            ui->t2_score_lineEdit->setEnabled(true);
            ui->t2_sdept_comboBox->setEnabled(true);
            ui->t2_sex_comboBox->setEnabled(true);

            ui->t2_birth_dateEdit->setDate(QDate::fromString(time, "yyyy-MM-dd"));
            ui->t2_name_lineEdit->setText(name);
            ui->t2_sex_comboBox->setCurrentText(sex);
            ui->t2_sdept_comboBox->setCurrentText(sdept_no_to_name[sdept_no]);
            ui->t2_score_lineEdit->setText(score);
        }
    }
}

void StudentUI::on_t2_m_pushButton_clicked()
{
    QString no = ui->t2_no_lineEdit->text();
    QString name = ui->t2_name_lineEdit->text();
    QString sex = ui->t2_sex_comboBox->currentText();
    QString birth = ui->t2_birth_dateEdit->text();
    QString ad_score = ui->t2_score_lineEdit->text();
    QString sdept_no;

    if(sdept_name_to_no.find(ui->t2_sdept_comboBox->currentText())
            == sdept_name_to_no.end()) {
        QMessageBox::critical(this, "错误", "系别输入错误");
        return;
    }

    if(name == "") {
        QMessageBox::critical(this, "错误", "姓名为空");
        return;
    }

    sdept_no = sdept_name_to_no[ui->t2_sdept_comboBox->currentText()];

    QString sql;

    sql = "select no from student "
          "where no = '%1' "
            ;

    sql = sql.arg(no);

    QSqlQuery ret;
    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        if(ret.size() == 0) {
            QMessageBox::critical(this, "错误", "该用户不存在");
            return;
        }
    }

    sql =
            "update student "
            "set name = '%1', sex = '%2', birth = '%3', ad_score = '%4', sdept_no = '%5' "
            "where no = '%6'; "
            ;

    sql = sql.arg(name, sex, birth, ad_score, sdept_no, no);

    if(!ret.exec(sql)) {
        QMessageBox::critical(this, "错误", ret.lastError().text());
    }
    else {
        QMessageBox::information(this, "信息", "修改成功!");
    }
}

void StudentUI::on_t3_pushButton_clicked()
{
    if(QMessageBox::Yes == QMessageBox::warning(this, "警告", "确定要删除选定学生?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No)) {
        qDebug() << "yes";
    }
    else {
        qDebug() << "no";
    }

    QLayout *layout = ui->t3_scrollAreaWidgetContents->layout();

    for(int i = 0; i < layout->count(); i++) {
        QLayoutItem *it = layout->itemAt(i);
        QCheckBox *pbox = qobject_cast<QCheckBox *>(it->widget());

        if(!pbox->isChecked()) continue;

        QString sql;

        sql =   "delete from user "
                "where no = '%1'; "
                ;

        sql = sql.arg(student_name_to_no[pbox->text()]);

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
