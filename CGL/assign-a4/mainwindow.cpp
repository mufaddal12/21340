#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <math.h>

const int win_x = 500;
const int win_y = 500;

QImage image(win_x, win_y, QImage::Format_RGB888);
QImage image2(256, 256, QImage::Format_RGB888);
QImage image3(20, 256, QImage::Format_RGB888);

void Point::addOffset(int x, int y)
{
    px -= x;
    py -= y;
}

bool Point::range(int x, int y, int offset_x, int offset_y)
{
    if(px>=x && px<(x + offset_x))
        if(py>=y && py<(y + offset_y))
            return true;
    return false;
}

void Polygon::addVertex(Point p)
{
    allPoints.push_back(p);
    vertices++;
}

Point Polygon::getFront()
{
    if(!isEmpty())
        return allPoints[vertices-1];
    else
    {
        Point p;
        return p;
    }
}

Point Polygon::getRear()
{
    if(!isEmpty())
        return allPoints[0];
    else
    {
        Point p;
        return p;
    }
}

int Polygon::isEmpty()
{
    return vertices==0;
}

void Polygon::clearPoly()
{
    vertices = 0;
    allPoints.clear();
}

void Polygon::changeColour(int r = 0, int g = 0 , int b = 0 )
{
    int R = qRed(fillColour);
    int G = qGreen(fillColour);
    int B = qBlue(fillColour);
    if(r != 0)
       R = r;
    if(b != 0)
        B = b;
    if(g != 0)
        G = g;
    fillColour = qRgb(R,G,B);
}

int sign(float val)
{
    if(val>0)
        return 1;
    else if(val<0)
        return -1;
    else
        return 0;
}

void drawLineDDA(Point p1, Point p2, QRgb value = qRgb(0,255,255))
{

    int x1 = p1.x(), x2 = p2.x(), y1 = p1.y(), y2 = p2.y();
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

void seedFill(int x, int y, QRgb fillColour, QRgb backColour = qRgb(0,0,0))
{
    if(image.pixel(x, y) != backColour)
        return;
    else
    {
        image.setPixel(x, y, fillColour);
        seedFill(x, y+1, fillColour);
        seedFill(x, y-1, fillColour);
        seedFill(x-1, y, fillColour);
        seedFill(x+1, y, fillColour);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 0; i<256; i++)
    {
        for(int j = 0; j<256; j++)
            image2.setPixel(i,j,qRgb(i,j,0));
        for(int j = 0; j<20; j++)
            image3.setPixel(j,i,qRgb(0,0,i));
    }


    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
    ui->palette->setPixmap(QPixmap::fromImage(image2));
    ui->palette->show();
    ui->palette_2->setPixmap(QPixmap::fromImage(image3));
    ui->palette_2->show();
}

void MainWindow::mousePressEvent(QMouseEvent *m)
{
    int x = m->x();
    int y = m->y();
    Point p(x, y);
    if(p.range(20, 20, win_x,win_y))
    {
        p.addOffset(20, 20);
        if(m->button() == Qt::LeftButton)
        {
            if(poly.isEmpty())
                poly.addVertex(p);
        }
        else if(m->button() == Qt::RightButton)
        {
            if(poly.isEmpty())
                poly.addVertex(p);
        }
        else if(m->button() == Qt::MidButton)
        {
            seedFill(p.x(), p.y(), poly.fillColour);
        }
    }
    else if(p.range(600, 20, 256, 256))
    {
        p.addOffset(600, 20);
        poly.changeColour(p.x(), p.y());
    }
    else if(p.range(860, 20, 30, 256))
    {
        p.addOffset(860, 20);
        poly.changeColour(0, 0, p.y());
    }
    //drawLineDDA();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *m)
{
    Point p(m->x(), m->y());
    if(p.range(20, 20, win_x,win_y))
    {
        p.addOffset(20, 20);
        if(m->button() == Qt::LeftButton)
        {
            drawLineDDA(p, poly.getFront());
            poly.addVertex(p);
        }
        else if(m->button() == Qt::RightButton)
        {
            drawLineDDA(poly.getRear(), poly.getFront());
            poly.addVertex(poly.getRear());
        }
    }


    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clear_clicked()
{
    for(int i = 0; i<win_x; i++)
        for(int j = 0; j<win_y; j++)
            image.setPixel(i,j,qRgb(0,0,0));
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
    poly.clearPoly();
}
