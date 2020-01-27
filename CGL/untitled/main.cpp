#include "mainwindow.h"
#include <QApplication>
#include<QtGui>
#include<math.h>
QImage drawLine(int x1, int x2, int y1, int y2, QRgb value)
{
    QImage image(300, 300, QImage::Format_RGB888);

    int h = 300, k = 50;

    for(int x=0;x<200;x++)
    {
        int y = -m*(x - h) - k;
        image.setPixel(x,y,value);
    }
    return image;
}

QImage drawCircle(int x1, int y1, int rad, QRgb value)
{
    QImage image(2*rad+50, 2*rad+50, QImage::Format_RGB888);
    int dyu, dyd;
    for(int x = x1-rad; x<=x1+rad;x++)
    {
        dyu = y1 + int(sqrt(rad*rad - (x - x1)*(x - x1)));
        dyd = y1 - int(sqrt(rad*rad - (x - x1)*(x - x1)));
        image.setPixel(x,dyu,value);
        image.setPixel(x,dyd ,value);
    }
    return image;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QRgb value;
    value=qRgb(0,255,0);   //set color of pixel as green

    //drawing line
    int x1 = 0, x2 = 20, y1 = 0, y2 = 20;
    QImage image = drawLine(x1, x2, y1, y2, value); //draws pixel in white color at x,y
    //QImage image = drawLine(50, 200, 60, 260, value);
    //drawing circle
    //int cx = 300, cy = 300, rad = 300;
    //QImage image = drawCircle(cx, cy, rad, value);                              //position.
    QLabel l;                              //shows pixel on screen
    l.setPixmap(QPixmap::fromImage(image));
    l.show();
    return a.exec();
}
