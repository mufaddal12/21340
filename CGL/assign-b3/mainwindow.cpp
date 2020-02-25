#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QMouseEvent>

const int win_x = 500;
const int win_y = 500;

QImage image(win_x, win_y, QImage::Format_RGB888);

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

void Point::change(int xn, int yn)
{
    px = xn;
    py = yn;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::changeViewPoly(Point p)
{
    bool l = false, r = false, u = false, b = false;
    int x = p.x();
    int y = p.y();
    if(x<A.x())
        l = true;
    if(x>D.x())
        r = true;
    if(y<A.y())
        u = true;
    if(y>B.y())
        b = true;
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
            if(actualPoly.isEmpty())
            {

                actualPoly.addVertex(p);


            }
            else
            {
                actualPoly.addVertex(p);
                Point p1 = actualPoly.getFront();

                changeViewPoly(p1);
            }
        }
        else if(m->button() == Qt::RightButton)
        {
            if(actualPoly.isEmpty())
                actualPoly.addVertex(p);
            else
            {

            }
        }

    }
}

void MainWindow::on_pushButton_clicked()
{
    int x1 = ui->x1->toPlainText().toInt();
    int y1 = ui->y1->toPlainText().toInt();
    int x2 = ui->x2->toPlainText().toInt();
    int y2 = ui->y2->toPlainText().toInt();
    drawLineDDA(A,B, qRgb(0,0,0));
    drawLineDDA(B,C, qRgb(0,0,0));
    drawLineDDA(C,D, qRgb(0,0,0));
    drawLineDDA(D,A, qRgb(0,0,0));
    A.change(x1,y1), B.change(x1, y2), C.change(x2,y2), D.change(x2, y1);
    drawLineDDA(A,B);
    drawLineDDA(B,C);
    drawLineDDA(C,D);
    drawLineDDA(D,A);
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}


























MainWindow::~MainWindow()
{
    delete ui;
}

