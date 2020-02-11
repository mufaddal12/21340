#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <math.h>

const int win_x = 500;
const int win_y = 500;

QImage image(win_x, win_y, QImage::Format_RGB888);
QImage image2(256, 256, QImage::Format_RGB888);

int sign(float val)
{
    if(val>0)
        return 1;
    else if(val<0)
        return -1;
    else
        return 0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 0; i<256; i++)
        for(int j = 0; j<256; j++)
            image2.setPixel(i,j,qRgb(0,i,j));

    ui->palette->setPixmap(QPixmap::fromImage(image2));
    ui->palette->show();
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::mousePressEvent(QMouseEvent *m)
{
    int x = m->x();
    int y = m->y();

    Point p(x,y);
    poly.addPoint(p);
    //drawLineDDA();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *m)
{
    Point p(m->x(), m->y());

    poly.addPoint(p);
    drawLineDDA(p, poly.getTop());
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::drawLineDDA(Point p1, Point p2, QRgb value)
{

    int x1 = p1.x, x2 = p2.x, y1 = p1.y, y2 = p2.y;
    int length;
    if(abs(x2-x1) > abs(y2-y1))
        length = abs(x2-x1);
    else
        length = abs(y2-y1);
    float delta_x = (x2-x1)/float(length);
    float delta_y = (y2-y1)/float(length);

    float x = x1 + 0.5*sign(delta_x);
    float y = y1 + 0.5*sign(delta_y);

    for(int i = 0; i< length; i++)
    {
        image.setPixel(int(floor(x)),int(floor(y)), value);
        x = x + delta_x;
        y = y + delta_y;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
