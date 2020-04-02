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
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_10;
    QTextEdit *x;
    QLabel *label_8;
    QLabel *label_9;
    QTextEdit *y;
    QLabel *window;
    QPushButton *rotate;
    QPushButton *input;
    QTextEdit *theta;
    QRadioButton *xaxis;
    QRadioButton *yaxis;
    QPushButton *reflect;
    QLabel *label_11;
    QLabel *label_12;
    QTextEdit *x_2;
    QTextEdit *y_2;
    QLabel *label_13;
    QLabel *label_14;
    QRadioButton *xy;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(762, 588);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(650, 40, 21, 31));
        x = new QTextEdit(centralWidget);
        x->setObjectName(QString::fromUtf8("x"));
        x->setGeometry(QRect(600, 40, 41, 31));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(570, 390, 111, 17));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(570, 40, 21, 31));
        y = new QTextEdit(centralWidget);
        y->setObjectName(QString::fromUtf8("y"));
        y->setGeometry(QRect(680, 40, 41, 31));
        window = new QLabel(centralWidget);
        window->setObjectName(QString::fromUtf8("window"));
        window->setGeometry(QRect(0, 0, 500, 500));
        rotate = new QPushButton(centralWidget);
        rotate->setObjectName(QString::fromUtf8("rotate"));
        rotate->setGeometry(QRect(620, 430, 89, 25));
        input = new QPushButton(centralWidget);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(610, 80, 101, 25));
        theta = new QTextEdit(centralWidget);
        theta->setObjectName(QString::fromUtf8("theta"));
        theta->setGeometry(QRect(680, 380, 41, 31));
        xaxis = new QRadioButton(centralWidget);
        xaxis->setObjectName(QString::fromUtf8("xaxis"));
        xaxis->setGeometry(QRect(580, 180, 71, 23));
        yaxis = new QRadioButton(centralWidget);
        yaxis->setObjectName(QString::fromUtf8("yaxis"));
        yaxis->setGeometry(QRect(660, 180, 71, 23));
        reflect = new QPushButton(centralWidget);
        reflect->setObjectName(QString::fromUtf8("reflect"));
        reflect->setGeometry(QRect(610, 240, 89, 25));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(580, 340, 21, 31));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(660, 340, 21, 31));
        x_2 = new QTextEdit(centralWidget);
        x_2->setObjectName(QString::fromUtf8("x_2"));
        x_2->setGeometry(QRect(610, 340, 41, 31));
        y_2 = new QTextEdit(centralWidget);
        y_2->setObjectName(QString::fromUtf8("y_2"));
        y_2->setGeometry(QRect(690, 340, 41, 31));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(610, 310, 101, 31));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(610, 150, 101, 31));
        xy = new QRadioButton(centralWidget);
        xy->setObjectName(QString::fromUtf8("xy"));
        xy->setGeometry(QRect(620, 210, 71, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 762, 22));
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
        label_10->setText(QApplication::translate("MainWindow", "y : ", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Rotation Angle", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "x :", 0, QApplication::UnicodeUTF8));
        window->setText(QString());
        rotate->setText(QApplication::translate("MainWindow", "Rotate", 0, QApplication::UnicodeUTF8));
        input->setText(QApplication::translate("MainWindow", "Input Vertex", 0, QApplication::UnicodeUTF8));
        xaxis->setText(QApplication::translate("MainWindow", "X - Axis", 0, QApplication::UnicodeUTF8));
        yaxis->setText(QApplication::translate("MainWindow", "Y - Axis", 0, QApplication::UnicodeUTF8));
        reflect->setText(QApplication::translate("MainWindow", "Reflect", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "x :", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "y : ", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Rotation about", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Reflect About :", 0, QApplication::UnicodeUTF8));
        xy->setText(QApplication::translate("MainWindow", "X = Y", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
