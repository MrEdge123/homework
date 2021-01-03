/********************************************************************************
** Form generated from reading UI file 'filegetwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEGETWINDOW_H
#define UI_FILEGETWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileGetWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *FileGetWindow)
    {
        if (FileGetWindow->objectName().isEmpty())
            FileGetWindow->setObjectName(QStringLiteral("FileGetWindow"));
        FileGetWindow->resize(491, 91);
        verticalLayout = new QVBoxLayout(FileGetWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(FileGetWindow);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(FileGetWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(FileGetWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FileGetWindow);

        QMetaObject::connectSlotsByName(FileGetWindow);
    } // setupUi

    void retranslateUi(QWidget *FileGetWindow)
    {
        FileGetWindow->setWindowTitle(QApplication::translate("FileGetWindow", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("FileGetWindow", "\346\230\257\345\220\246\346\216\245\346\224\266\346\226\207\344\273\266\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FileGetWindow", "\346\216\245\346\224\266", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FileGetWindow", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FileGetWindow: public Ui_FileGetWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEGETWINDOW_H
