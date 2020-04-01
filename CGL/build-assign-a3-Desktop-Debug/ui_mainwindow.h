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
    QPushButton *scale;
    QPushButton *translate;
    QPushButton *rotate;
    QLabel *label_8;
    QTextEdit *theta;
    QTextEdit *y;
    QLabel *label_9;
    QTextEdit *x;
    QLabel *label_10;
    QPushButton *input;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(789, 613);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        window = new QLabel(centralWidget);
        window->setObjectName(QString::fromUtf8("window"));
        window->setGeometry(QRect(20, 20, 500, 500));
        scale = new QPushButton(centralWidget);
        scale->setObjectName(QString::fromUtf8("scale"));
        scale->setGeometry(QRect(580, 130, 89, 25));
        translate = new QPushButton(centralWidget);
        translate->setObjectName(QString::fromUtf8("translate"));
        translate->setGeometry(QRect(680, 130, 89, 25));
        rotate = new QPushButton(centralWidget);
        rotate->setObjectName(QString::fromUtf8("rotate"));
        rotate->setGeometry(QRect(690, 170, 89, 25));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(530, 180, 111, 17));
        theta = new QTextEdit(centralWidget);
        theta->setObjectName(QString::fromUtf8("theta"));
        theta->setGeometry(QRect(640, 170, 41, 31));
        y = new QTextEdit(centralWidget);
        y->setObjectName(QString::fromUtf8("y"));
        y->setGeometry(QRect(700, 60, 41, 31));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(590, 60, 21, 31));
        x = new QTextEdit(centralWidget);
        x->setObjectName(QString::fromUtf8("x"));
        x->setGeometry(QRect(620, 60, 41, 31));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(670, 60, 21, 31));
        input = new QPushButton(centralWidget);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(630, 100, 101, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 789, 22));
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
        scale->setText(QApplication::translate("MainWindow", "Scale", 0, QApplication::UnicodeUTF8));
        translate->setText(QApplication::translate("MainWindow", "Translate", 0, QApplication::UnicodeUTF8));
        rotate->setText(QApplication::translate("MainWindow", "Rotate", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Rotation Angle", 0, QApplication::UnicodeUTF8));
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
