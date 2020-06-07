/********************************************************************************
** Form generated from reading UI file 'reswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESWINDOW_H
#define UI_RESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ResWindow
{
public:

    void setupUi(QDialog *ResWindow)
    {
        if (ResWindow->objectName().isEmpty())
            ResWindow->setObjectName(QString::fromUtf8("ResWindow"));
        ResWindow->resize(469, 350);

        retranslateUi(ResWindow);

        QMetaObject::connectSlotsByName(ResWindow);
    } // setupUi

    void retranslateUi(QDialog *ResWindow)
    {
        ResWindow->setWindowTitle(QCoreApplication::translate("ResWindow", "Result", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResWindow: public Ui_ResWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESWINDOW_H
