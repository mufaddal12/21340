#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <math.h>
#include<QString>
#define PI 3.14

const int win_x = 500;
const int win_y = 500;

const int org_x = win_x/2;
const int org_y = win_y/2;

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
    drawLineDDA(tl, br, qRgb(50,50,50));
    drawLineDDA(tr, bl, qRgb(50,50,50));
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
    float val = PI/180;
    float rad = theta*val;
    Matrix scale;
    QVector<float> row;
    row.push_back(cos(rad));
    row.push_back(sin(rad));
    row.push_back(0);
    scale.addRow(row);
    row.clear();
    row.push_back(-sin(rad));
    row.push_back(cos(rad));
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

void Polygon::translate(int x, int y)
{
    Matrix transActual = getTranslationMatrix(x,y);
    allPoints = allPoints * transActual;
}

void Polygon::rotate(int theta, int x, int y)
{
    if(x==-1)
    {
        float mid_x = 0, mid_y = 0;
        for(int r = 0; r<vertices-1; r++)
        {
            QVector<float> p = allPoints.getRow(r);
            mid_x += p[0];
            mid_y += p[1];
        }
        mid_x /= float(vertices-1);
        mid_y /= float(vertices-1);
        x = floor(mid_x); y = floor(mid_y);
    }

    Matrix trans = getTranslationMatrix(-x, -y);
    allPoints = allPoints * trans;
    Matrix rot = getRotationMatrix(theta);
    allPoints = allPoints * rot;
    trans = getTranslationMatrix(x, y);
    allPoints = allPoints * trans;
}

void Polygon::reflectAboutX()
{
    Matrix reflect = getReflectAboutXMatrix();
    allPoints = allPoints * reflect;
}

void Polygon::reflectAboutY()
{
    Matrix reflect = getReflectAboutYMatrix();
    allPoints = allPoints * reflect;
}

void Polygon::reflectAboutX_Y()
{
    Matrix reflect = getReflectAboutX_YMatrix();
    allPoints = allPoints * reflect;
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
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::on_rotate_clicked()
{
    QString sx = ui->x_2->toPlainText();
    if(sx=="")
    {
        int theta = ui->theta->toPlainText().toInt();
        poly.rotate(theta);
        clearScreen();
        poly.display();
    }
    else
    {
        int x = ui->x_2->toPlainText().toInt();
        int y = ui->y_2->toPlainText().toInt();
        int theta = ui->theta->toPlainText().toInt();
        poly.rotate(theta, x, y);
        clearScreen();
        poly.display();
    }
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::on_input_clicked()
{
    int x = ui->x->toPlainText().toInt();
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
    ui->window->show();
}


void MainWindow::on_reflect_clicked()
{
    if(ui->xaxis->isChecked())
    {
        poly.reflectAboutX();
        clearScreen();
        poly.display();
    }
    else if(ui->yaxis->isChecked())
    {
        poly.reflectAboutY();
        clearScreen();
        poly.display();
    }
    else if(ui->xy->isChecked())
    {
        poly.reflectAboutX_Y();
        clearScreen();
        poly.display();
    }
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


