/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *x1;
    QTextEdit *y1;
    QTextEdit *x2;
    QTextEdit *y2;
    QPushButton *solid;
    QPushButton *dotted;
    QPushButton *dashed;
    QPushButton *dashDot;
    QPushButton *thick;
    QLabel *window;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(966, 625);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 40, 65, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 80, 65, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 120, 65, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 160, 65, 21));
        x1 = new QTextEdit(centralWidget);
        x1->setObjectName(QString::fromUtf8("x1"));
        x1->setGeometry(QRect(100, 30, 104, 31));
        y1 = new QTextEdit(centralWidget);
        y1->setObjectName(QString::fromUtf8("y1"));
        y1->setGeometry(QRect(100, 70, 104, 31));
        x2 = new QTextEdit(centralWidget);
        x2->setObjectName(QString::fromUtf8("x2"));
        x2->setGeometry(QRect(100, 110, 104, 31));
        y2 = new QTextEdit(centralWidget);
        y2->setObjectName(QString::fromUtf8("y2"));
        y2->setGeometry(QRect(100, 150, 104, 31));
        solid = new QPushButton(centralWidget);
        solid->setObjectName(QString::fromUtf8("solid"));
        solid->setGeometry(QRect(20, 210, 97, 31));
        dotted = new QPushButton(centralWidget);
        dotted->setObjectName(QString::fromUtf8("dotted"));
        dotted->setGeometry(QRect(130, 210, 97, 31));
        dashed = new QPushButton(centralWidget);
        dashed->setObjectName(QString::fromUtf8("dashed"));
        dashed->setGeometry(QRect(20, 250, 97, 31));
        dashDot = new QPushButton(centralWidget);
        dashDot->setObjectName(QString::fromUtf8("dashDot"));
        dashDot->setGeometry(QRect(130, 250, 97, 31));
        thick = new QPushButton(centralWidget);
        thick->setObjectName(QString::fromUtf8("thick"));
        thick->setGeometry(QRect(70, 290, 97, 31));
        window = new QLabel(centralWidget);
        window->setObjectName(QString::fromUtf8("window"));
        window->setGeometry(QRect(310, 30, 541, 511));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 966, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "X1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Y1", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "X2", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Y2", 0, QApplication::UnicodeUTF8));
        solid->setText(QApplication::translate("MainWindow", "Solid", 0, QApplication::UnicodeUTF8));
        dotted->setText(QApplication::translate("MainWindow", "Dotted", 0, QApplication::UnicodeUTF8));
        dashed->setText(QApplication::translate("MainWindow", "Dashed", 0, QApplication::UnicodeUTF8));
        dashDot->setText(QApplication::translate("MainWindow", "Dash Dot", 0, QApplication::UnicodeUTF8));
        thick->setText(QApplication::translate("MainWindow", "Thick", 0, QApplication::UnicodeUTF8));
        window->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
