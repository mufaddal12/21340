/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
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
    QLabel *window;
    QPushButton *next;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *input;
    QTextEdit *y;
    QTextEdit *x;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 586);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        window = new QLabel(centralWidget);
        window->setObjectName(QString::fromUtf8("window"));
        window->setGeometry(QRect(0, 0, 500, 500));
        next = new QPushButton(centralWidget);
        next->setObjectName(QString::fromUtf8("next"));
        next->setGeometry(QRect(610, 190, 89, 25));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(570, 40, 21, 31));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(650, 40, 21, 31));
        input = new QPushButton(centralWidget);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(610, 80, 101, 25));
        y = new QTextEdit(centralWidget);
        y->setObjectName(QString::fromUtf8("y"));
        y->setGeometry(QRect(680, 40, 41, 31));
        x = new QTextEdit(centralWidget);
        x->setObjectName(QString::fromUtf8("x"));
        x->setGeometry(QRect(600, 40, 41, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
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
        window->setText(QString());
        next->setText(QApplication::translate("MainWindow", "Next Curve", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "x :", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "y : ", 0, QApplication::UnicodeUTF8));
        input->setText(QApplication::translate("MainWindow", "Input Vertex", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
