/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit_temin;
    QLineEdit *lineEdit_metavar;
    QPushButton *pushButton;
    QPlainTextEdit *plainTextEdit_2_nonterm;
    QPlainTextEdit *plainTextEdit_gramm;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_5;
    QFrame *line_2;
    QFrame *line;
    QPlainTextEdit *plainTextEdit_patt;
    QPlainTextEdit *plainTextEdit_regexp;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QPlainTextEdit *plainTextEdit_prog;
    QLabel *label_7;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1120, 653);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        plainTextEdit_temin = new QPlainTextEdit(centralwidget);
        plainTextEdit_temin->setObjectName(QString::fromUtf8("plainTextEdit_temin"));

        gridLayout->addWidget(plainTextEdit_temin, 7, 0, 1, 1);

        lineEdit_metavar = new QLineEdit(centralwidget);
        lineEdit_metavar->setObjectName(QString::fromUtf8("lineEdit_metavar"));

        gridLayout->addWidget(lineEdit_metavar, 10, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 10, 9, 1, 1);

        plainTextEdit_2_nonterm = new QPlainTextEdit(centralwidget);
        plainTextEdit_2_nonterm->setObjectName(QString::fromUtf8("plainTextEdit_2_nonterm"));

        gridLayout->addWidget(plainTextEdit_2_nonterm, 1, 5, 1, 1);

        plainTextEdit_gramm = new QPlainTextEdit(centralwidget);
        plainTextEdit_gramm->setObjectName(QString::fromUtf8("plainTextEdit_gramm"));

        gridLayout->addWidget(plainTextEdit_gramm, 1, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 9, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 7, 1, 1);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 7, 7, 1, 1);

        plainTextEdit_patt = new QPlainTextEdit(centralwidget);
        plainTextEdit_patt->setObjectName(QString::fromUtf8("plainTextEdit_patt"));

        gridLayout->addWidget(plainTextEdit_patt, 1, 9, 1, 1);

        plainTextEdit_regexp = new QPlainTextEdit(centralwidget);
        plainTextEdit_regexp->setObjectName(QString::fromUtf8("plainTextEdit_regexp"));

        gridLayout->addWidget(plainTextEdit_regexp, 7, 5, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 9, 1, 1);

        horizontalSpacer = new QSpacerItem(3, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 6, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 5, 1, 1);

        plainTextEdit_prog = new QPlainTextEdit(centralwidget);
        plainTextEdit_prog->setObjectName(QString::fromUtf8("plainTextEdit_prog"));

        gridLayout->addWidget(plainTextEdit_prog, 7, 9, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 9, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(3, 1, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 8, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1120, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Reflexive Parser", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Match", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Grammar:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Program:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Terminals:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Pattern:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Regular expressions:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Metavariable Specifier:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "NonTerminals:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
