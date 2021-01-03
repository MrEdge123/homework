/********************************************************************************
** Form generated from reading UI file 'fileprogresswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEPROGRESSWINDOW_H
#define UI_FILEPROGRESSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileProgressWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *FileProgressWindow)
    {
        if (FileProgressWindow->objectName().isEmpty())
            FileProgressWindow->setObjectName(QStringLiteral("FileProgressWindow"));
        FileProgressWindow->resize(552, 84);
        verticalLayout = new QVBoxLayout(FileProgressWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(FileProgressWindow);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(FileProgressWindow);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setStyleSheet(QStringLiteral(""));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(FileProgressWindow);

        QMetaObject::connectSlotsByName(FileProgressWindow);
    } // setupUi

    void retranslateUi(QWidget *FileProgressWindow)
    {
        FileProgressWindow->setWindowTitle(QApplication::translate("FileProgressWindow", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("FileProgressWindow", "\346\226\207\344\273\266\345\220\215\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FileProgressWindow: public Ui_FileProgressWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEPROGRESSWINDOW_H
