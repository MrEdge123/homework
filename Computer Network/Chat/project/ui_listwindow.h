/********************************************************************************
** Form generated from reading UI file 'listwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTWINDOW_H
#define UI_LISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *userName;
    QListWidget *userList;

    void setupUi(QWidget *ListWindow)
    {
        if (ListWindow->objectName().isEmpty())
            ListWindow->setObjectName(QStringLiteral("ListWindow"));
        ListWindow->resize(367, 617);
        verticalLayout = new QVBoxLayout(ListWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(ListWindow);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        userName = new QLabel(ListWindow);
        userName->setObjectName(QStringLiteral("userName"));
        userName->setFont(font);
        userName->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(userName);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 5);

        verticalLayout->addLayout(horizontalLayout);

        userList = new QListWidget(ListWindow);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(userList);
        __qlistwidgetitem->setTextAlignment(Qt::AlignCenter);
        __qlistwidgetitem->setFlags(Qt::ItemIsEnabled);
        userList->setObjectName(QStringLiteral("userList"));

        verticalLayout->addWidget(userList);


        retranslateUi(ListWindow);

        QMetaObject::connectSlotsByName(ListWindow);
    } // setupUi

    void retranslateUi(QWidget *ListWindow)
    {
        ListWindow->setWindowTitle(QApplication::translate("ListWindow", "ListWindow", Q_NULLPTR));
        label->setText(QApplication::translate("ListWindow", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        userName->setText(QApplication::translate("ListWindow", "TextLabel", Q_NULLPTR));

        const bool __sortingEnabled = userList->isSortingEnabled();
        userList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = userList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("ListWindow", "\345\234\250\347\272\277\345\210\227\350\241\250", Q_NULLPTR));
        userList->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class ListWindow: public Ui_ListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTWINDOW_H
