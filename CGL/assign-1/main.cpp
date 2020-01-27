#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.on_pushButton_clicked();
   /* int x1, y1,len;
    x1 = 20;
    y1 = 10;
    len = 550;
    win_x = 600;
    win_y = 600;
    QImage image = drawFigure(x1,y1,len);

    QLabel l;
    l.setPixmap(QPixmap::fromImage(image));
    l.show();*/
    return a.exec();
}
