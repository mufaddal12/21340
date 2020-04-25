#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <math.h>
#include<QString>

const int win_x = 500;
const int win_y = 500;

const int org_x = win_x/2;
const int org_y = win_y/2;

const int side = 100;

QImage image(win_x, win_y, QImage::Format_RGB888);

void Matrix::addRow(Point p)
{
    int x = p.x();
    int y = p.y();
    QVector<float> row;
    row.push_back(float(x));
    row.push_back(float(y));
    row.push_back(1.0);
    addRow(row);
}

Matrix Matrix::operator *(const Matrix B)
{
    Matrix C;
    for(int r = 0; r<m; r++)
    {
        QVector<float> row;
        row.clear();
        for(int c = 0; c<B.n; c++)
        {
            float sum = 0;
            for(int k = 0; k<n; k++)
            {
                sum += (mat[r][k] * B.mat[k][c]);
            }
            row.push_back(sum);
        }
        C.addRow(row);
    }
    return C;
}

Matrix Matrix::operator +(const Matrix B)
{
    Matrix C;
    for(int p = 0; p<m; p++)
    {
        QVector<float> row = mat[p];
        C.addRow(row);
    }
    for(int p = 0; p<B.m; p++)
    {
        QVector<float> row = B.mat[p];
        C.addRow(row);
    }
    return C;
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
    int x1 = p1.x() + org_x, x2 = p2.x() + org_x, y1 = p1.y() + org_y, y2 = p2.y() + org_y;
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

void clearScreen()
{
    for(int i = 0; i<win_x; i++)
        for(int j = 0; j<win_y; j++)
            image.setPixel(i, j, qRgb(0,0,0));
    Point p1(0, -250), p2(0, 249), p3(-250, 0), p4(249, 0);
    Point tl(-250,-250), br(249, 249), bl(-250, 249), tr(249, -250);
    drawLineDDA(p1, p2, qRgb(50,50,50));
    drawLineDDA(p3, p4, qRgb(50,50,50));
   /* drawLineDDA(tl, br, qRgb(50,50,50));
    drawLineDDA(tr, bl, qRgb(50,50,50));*/
}

Matrix getScaleMatrix(float x, float y)
{
    Matrix scale;
    QVector<float> row;
    row.push_back(x);
    row.push_back(0);
    row.push_back(0);
    scale.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(y);
    row.push_back(0);
    scale.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(0);
    row.push_back(1);
    scale.addRow(row);
    return scale;
}

Matrix getTranslationMatrix(int x, int y)
{
    Matrix scale;
    QVector<float> row;
    row.push_back(1);
    row.push_back(0);
    row.push_back(0);
    scale.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(1);
    row.push_back(0);
    scale.addRow(row);
    row.clear();
    row.push_back(x);
    row.push_back(y);
    row.push_back(1);
    scale.addRow(row);
    return scale;
}

Matrix getRotationMatrix(int theta)
{
    int sin, cos;
    if(theta == 90)
    {
        sin = 1;
        cos = 0;
    }
    if(theta==-90)
    {
        sin = -1;
        cos = 0;
    }
    Matrix scale;
    QVector<float> row;
    row.push_back(cos);
    row.push_back(sin);
    row.push_back(0);
    scale.addRow(row);
    row.clear();
    row.push_back(-sin);
    row.push_back(cos);
    row.push_back(0);
    scale.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(0);
    row.push_back(1);
    scale.addRow(row);
    return scale;
}

Matrix getReflectAboutXMatrix()
{
    Matrix ref;
    QVector<float> row;
    row.push_back(1);
    row.push_back(0);
    row.push_back(0);
    ref.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(-1);
    row.push_back(0);
    ref.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(0);
    row.push_back(1);
    ref.addRow(row);
    return ref;
}

Matrix getReflectAboutYMatrix()
{
    Matrix ref;
    QVector<float> row;
    row.push_back(-1);
    row.push_back(0);
    row.push_back(0);
    ref.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(1);
    row.push_back(0);
    ref.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(0);
    row.push_back(1);
    ref.addRow(row);
    return ref;
}

Matrix getReflectAboutX_YMatrix()
{
    Matrix ref;
    QVector<float> row;
    row.push_back(0);
    row.push_back(1);
    row.push_back(0);
    ref.addRow(row);
    row.clear();
    row.push_back(1);
    row.push_back(0);
    row.push_back(0);
    ref.addRow(row);
    row.clear();
    row.push_back(0);
    row.push_back(0);
    row.push_back(1);
    ref.addRow(row);
    return ref;
}

void Point::addOffset(int x, int y)
{
    px -= x;
    py -= y;
}

void Polygon::addVertex(Point p)
{
    allPoints.addRow(p);
    vertices++;
}

Point Polygon::getPoint(int i)
{
    QVector<float> row = allPoints.getRow(i);
    Point p(row[0], row[1]);
    return p;
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
    {
        return getPoint(0);
    }
    else
    {
        Point p;
        return p;
    }
}

Point Polygon::getRear()
{
    if(!isEmpty())
    {
        return getPoint(vertices - 1);
    }
    else
    {
        Point p;
        return p;
    }
}

void Polygon::scale(float x, float y)
{
    Matrix scale = getScaleMatrix(x,y);
    float mid_x = 0, mid_y = 0;
    for(int r = 0; r<vertices; r++)
    {
        QVector<float> p = allPoints.getRow(r);
        mid_x += p[0];
        mid_y += p[1];
    }
    mid_x /= float(vertices);
    mid_y /= float(vertices);

    Matrix trans = getTranslationMatrix(floor(-mid_x), floor(-mid_y));
    //allPoints = allPoints * trans;
    allPoints = allPoints * scale;
    trans = getTranslationMatrix(floor(mid_x), floor(mid_y));
    //allPoints = allPoints * trans;
}

void Polygon::translate(int x, int y)
{
    Matrix transActual = getTranslationMatrix(x,y);
    allPoints = allPoints * transActual;
}

void Polygon::rotate(int theta, int x, int y)
{
    Matrix rot = getRotationMatrix(theta);
    allPoints = allPoints * rot;
}

void Polygon::reflectAboutX()
{
    Matrix reflect = getReflectAboutXMatrix();
    allPoints = allPoints * reflect;
}

void Polygon::getNextHilbert()
{
    scale(0.5, 0.5);
    Polygon quad34(allPoints), quad1(allPoints), quad2(allPoints);
    quad34.reflectAboutX();
    Polygon quad3(quad34.allPoints), quad4(quad34.allPoints);
    quad1.translate(side, -side);
    quad2.translate(-side, -side);
    quad3.rotate(-90); quad3.translate(-side, side);
    quad4.rotate(90); quad4.translate(side, side);
    allPoints = quad3.allPoints;
    vertices = quad3.vertices;
    allPoints = allPoints + quad2.allPoints;
    vertices += quad2.vertices;
    allPoints = allPoints + quad1.allPoints;
    vertices += quad1.vertices;
    allPoints = allPoints + quad4.allPoints;
    vertices += quad4.vertices;
}

void Polygon::display(int off_x, int off_y)
{
    for(int i = 1; i<vertices; i++)
    {
        QVector<float> row = allPoints.getRow(i-1);
        Point p1(floor(row[0]), floor(row[1]));
        row = allPoints.getRow(i);
        Point p2(floor(row[0]), floor(row[1]));

        drawLineDDA(p1, p2, lineColour);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image.setPixel(0, 0, qRgb(0,0,0));
    clearScreen();

    Point p1(-side,side);
    poly.addVertex(p1);

    Point p2(-side,-side);
    poly.addVertex(p2);

    Point p3(side,-side);
    poly.addVertex(p3);

    Point p4(side,side);
    poly.addVertex(p4);

    poly.display();
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::on_input_clicked()
{
    /*int x = ui->x->toPlainText().toInt();
    int y = ui->y->toPlainText().toInt();
    Point p(x, y);
    if(poly.isEmpty())
    {
        poly.addVertex(p);
    }
    else
    {
        drawLineDDA(p, poly.getRear(), poly.lineColour);
        poly.addVertex(p);
    }
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();*/
}


void MainWindow::on_next_clicked()
{
    poly.getNextHilbert();
    clearScreen();
    poly.display();
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}


MainWindow::~MainWindow()
{
    delete ui;
}


