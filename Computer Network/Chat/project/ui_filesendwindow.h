/********************************************************************************
** Form generated from reading UI file 'filesendwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESENDWINDOW_H
#define UI_FILESENDWINDOW_H

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

class Ui_FileSendWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *FileSendWindow)
    {
        if (FileSendWindow->objectName().isEmpty())
            FileSendWindow->setObjectName(QStringLiteral("FileSendWindow"));
        FileSendWindow->resize(540, 100);
        verticalLayout = new QVBoxLayout(FileSendWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(FileSendWindow);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(FileSendWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QFont font1;
        font1.setPointSize(9);
        pushButton->setFont(font1);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(FileSendWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setFont(font1);

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FileSendWindow);

        QMetaObject::connectSlotsByName(FileSendWindow);
    } // setupUi

    void retranslateUi(QWidget *FileSendWindow)
    {
        FileSendWindow->setWindowTitle(QApplication::translate("FileSendWindow", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("FileSendWindow", "\347\241\256\345\256\232\350\246\201\345\217\221\351\200\201\346\226\207\344\273\266\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FileSendWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FileSendWindow", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FileSendWindow: public Ui_FileSendWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESENDWINDOW_H
