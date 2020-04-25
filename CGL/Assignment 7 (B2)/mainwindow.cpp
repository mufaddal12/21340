#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <math.h>

const int win_x = 500;
const int win_y = 500;

QImage image(win_x, win_y, QImage::Format_RGB888);
QImage image2(256, 256, QImage::Format_RGB888);
QImage image3(20, 256, QImage::Format_RGB888);

void fillPalette(int b = 0)
{
    for(int i = 0; i<256; i++)
        for(int j = 0; j<256; j++)
            image2.setPixel(i,j,qRgb(i,j,b));
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
    if(fillColour != backColour)
    {
        if(x>=0 && x<win_x && y>=0 && y<win_y)
        {
            if(image.pixel(x, y) != backColour)
                return;
            else
            {
                image.setPixel(x, y, fillColour);
                seedFill(x, y+1, fillColour, backColour);
                seedFill(x, y-1, fillColour, backColour);
                seedFill(x-1, y, fillColour, backColour);
                seedFill(x+1, y, fillColour, backColour);
            }
        }
    }
}

void Point::addOffset(int x, int y)
{
    px -= x;
    py -= y;
}

void Polygon::addVertex(Point p)
{
    allPoints.push_back(p);
    vertices++;
}

void Polygon::clearPoly()
{
    vertices = 0;
    allPoints.clear();
}

void Polygon::changeFillColour(QRgb val)
{
    fillColour = val;
}

void Polygon::changeLineColour(QRgb val)
{
    lineColour = val;
}

bool Point::range(int x, int y, int offset_x, int offset_y)
{
    if(px>=x && px<(x + offset_x))
        if(py>=y && py<(y + offset_y))
            return true;
    return false;
}

bool Polygon::isEmpty()
{
    return vertices==0;
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 0; i<256; i++)
    {
        for(int j = 0; j<20; j++)
            image3.setPixel(j,i,qRgb(0,0,i));
    }
    fillPalette();
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
            QRgb back = image.pixel(p.x(), p.y());
            seedFill(p.x(), p.y(), poly.fillColour, back);
        }
    }
    else if(p.range(600, 20, 256, 256))
    {
        p.addOffset(600, 20);
        poly.changeFillColour(image2.pixel(p.x(), p.y()));
    }
    else if(p.range(860, 20, 30, 256))
    {
        p.addOffset(860, 20);
        fillPalette(p.y());
        ui->palette->setPixmap(QPixmap::fromImage(image2));
        ui->palette->show();
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
            drawLineDDA(p, poly.getFront(), poly.lineColour);
            poly.addVertex(p);
        }
        else if(m->button() == Qt::RightButton)
        {
            drawLineDDA(poly.getRear(), poly.getFront(), poly.lineColour);
            poly.addVertex(poly.getRear());
        }
    }
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
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

void MainWindow::changeDisplay(QRgb val)
{
    QImage colour(50, 50, QImage::Format_RGB888);
    for(int i = 0; i<50; i++)
        for(int j = 0; j<50; j++)
            colour.setPixel(i,j, val);
    ui->colour->setPixmap(QPixmap::fromImage(colour));
    ui->colour->show();
}

void MainWindow::on_red_valueChanged(int value)
{
    int r = value;
    int g = ui->green->value();
    int b = ui->blue->value();
    QRgb clr = qRgb(r,g,b);
    changeDisplay(clr);

    QImage colour(20, 20, QImage::Format_RGB888);
    for(int i = 0; i<20; i++)
        for(int j = 0; j<20; j++)
            colour.setPixel(i,j, qRgb(r,0,0));
    ui->red_label->setPixmap(QPixmap::fromImage(colour));
    ui->red_label->show();

    poly.changeFillColour(clr);
}

void MainWindow::on_green_valueChanged(int value)
{
    int r = ui->red->value();
    int g = value;
    int b = ui->blue->value();
    QRgb clr = qRgb(r,g,b);
    changeDisplay(clr);

    QImage colour(20, 20, QImage::Format_RGB888);
    for(int i = 0; i<20; i++)
        for(int j = 0; j<20; j++)
            colour.setPixel(i,j, qRgb(0,g,0));
    ui->green_label->setPixmap(QPixmap::fromImage(colour));
    ui->green_label->show();

    poly.changeFillColour(clr);
}

void MainWindow::on_blue_valueChanged(int value)
{
    int r =  ui->red->value();
    int g = ui->green->value();
    int b = value;
    QRgb clr = qRgb(r,g,b);
    changeDisplay(clr);

    QImage colour(20, 20, QImage::Format_RGB888);
    for(int i = 0; i<20; i++)
        for(int j = 0; j<20; j++)
            colour.setPixel(i,j, qRgb(0,0,b));
    ui->blue_label->setPixmap(QPixmap::fromImage(colour));
    ui->blue_label->show();

    poly.changeFillColour(clr);
}

MainWindow::~MainWindow()
{
    delete ui;
}






