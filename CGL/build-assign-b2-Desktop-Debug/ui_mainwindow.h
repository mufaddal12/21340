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
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *window;
    QLabel *palette;
    QPushButton *clear;
    QLabel *palette_2;
    QSlider *red;
    QSlider *green;
    QSlider *blue;
    QLabel *colour;
    QLabel *red_label;
    QLabel *green_label;
    QLabel *blue_label;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(971, 587);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        window = new QLabel(centralWidget);
        window->setObjectName(QString::fromUtf8("window"));
        window->setGeometry(QRect(20, 20, 500, 500));
        window->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        palette = new QLabel(centralWidget);
        palette->setObjectName(QString::fromUtf8("palette"));
        palette->setGeometry(QRect(600, 20, 256, 256));
        clear = new QPushButton(centralWidget);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(580, 300, 89, 25));
        palette_2 = new QLabel(centralWidget);
        palette_2->setObjectName(QString::fromUtf8("palette_2"));
        palette_2->setGeometry(QRect(860, 20, 30, 256));
        red = new QSlider(centralWidget);
        red->setObjectName(QString::fromUtf8("red"));
        red->setGeometry(QRect(620, 350, 200, 20));
        red->setMaximum(255);
        red->setOrientation(Qt::Horizontal);
        green = new QSlider(centralWidget);
        green->setObjectName(QString::fromUtf8("green"));
        green->setGeometry(QRect(620, 380, 200, 20));
        green->setMaximum(255);
        green->setOrientation(Qt::Horizontal);
        blue = new QSlider(centralWidget);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setGeometry(QRect(620, 410, 200, 20));
        blue->setMaximum(255);
        blue->setOrientation(Qt::Horizontal);
        colour = new QLabel(centralWidget);
        colour->setObjectName(QString::fromUtf8("colour"));
        colour->setGeometry(QRect(870, 360, 50, 50));
        red_label = new QLabel(centralWidget);
        red_label->setObjectName(QString::fromUtf8("red_label"));
        red_label->setGeometry(QRect(830, 350, 20, 20));
        green_label = new QLabel(centralWidget);
        green_label->setObjectName(QString::fromUtf8("green_label"));
        green_label->setGeometry(QRect(830, 380, 20, 20));
        blue_label = new QLabel(centralWidget);
        blue_label->setObjectName(QString::fromUtf8("blue_label"));
        blue_label->setGeometry(QRect(830, 410, 20, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(550, 350, 41, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(550, 380, 61, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(550, 410, 41, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 971, 22));
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        MainWindow->setMenuBar(menuBar);
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
        palette->setText(QString());
        clear->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        palette_2->setText(QString());
        colour->setText(QString());
        red_label->setText(QString());
        green_label->setText(QString());
        blue_label->setText(QString());
        label->setText(QApplication::translate("MainWindow", "RED", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "GREEN", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "BLUE", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
