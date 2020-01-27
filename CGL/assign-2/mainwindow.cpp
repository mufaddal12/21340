#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

int win_x = 300;
int win_y = 300;

QImage image(win_x,win_y, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    int x1, y1, x2, y2;
    x1 = ui->textEdit_4->toPlainText().toInt();
    y1 = ui->textEdit_5->toPlainText().toInt();
    x2 = ui->textEdit_6->toPlainText().toInt();
    y2 = ui->textEdit_7->toPlainText().toInt();
    drawLineDDA(x1,y1,x2,y2);
    ui->label_8->setPixmap(QPixmap::fromImage(image));
    ui->label_8->show();
}

void MainWindow::on_pushButton_clicked()
{
    int cx, cy, rad;
    cx = ui->textEdit->toPlainText().toInt();
    cy = ui->textEdit_2->toPlainText().toInt();
    rad = ui->textEdit_3->toPlainText().toInt();
    drawCircleDDA(cx, cy, rad);
    ui->label_8->setPixmap(QPixmap::fromImage(image));
    ui->label_8->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    int cx, cy, rad;
    cx = ui->textEdit->toPlainText().toInt();
    cy = ui->textEdit_2->toPlainText().toInt();
    rad = ui->textEdit_3->toPlainText().toInt();
    drawCircleBRES(cx, cy, rad);
    ui->label_8->setPixmap(QPixmap::fromImage(image));
    ui->label_8->show();
}

void MainWindow::drawLineDDA(int x1, int y1, int x2, int y2)
{
    QRgb value;
    value = qRgb(0,255,255);

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

int MainWindow::sign(float val)
{
    if(val>0)
        return 1;
    else if(val<0)
        return -1;
    else
        return 0;
}

void MainWindow::mh(int &xi, int &delta_i)
{
    xi = xi + 1;
    delta_i = delta_i + 2*xi + 1;
}

void MainWindow::mv(int &yi, int &delta_i)
{
    yi = yi - 1;
    delta_i = delta_i - 2*yi + 1;
}

void MainWindow::md(int &xi, int &yi, int &delta_i)
{
    xi = xi + 1;
    yi = yi - 1;
    delta_i = delta_i + 2*xi -2*yi + 2;
}

void MainWindow::drawCircleBRES(int xc, int yc, int rad)
{
    QRgb value;
    value = qRgb(0,255,0);

    int xi = 0;
    int yi = rad;

    int delta_i = 2*(1 - rad);
    int limit = 0;
    while(yi>= limit)
    {
        image.setPixel(-xi + xc, -yi + yc, value);
        image.setPixel(-xi + xc, yi + yc, value);
        image.setPixel(xi + xc, -yi + yc, value);
        image.setPixel(xi + xc, yi + yc, value);
        int del;
        if(delta_i < 0)
        {
            del = 2*delta_i + 2 * yi - 1;
            if(del <= 0)
                mh(xi, delta_i);
            else
                md(xi,yi,delta_i);
        }
        else if(delta_i > 0)
        {
            del = 2*delta_i - 2*xi - 1;
            if(del<= 0)
                md(xi,yi,delta_i);
            else
                mv(yi, delta_i);
        }
        else
            md(xi, yi, delta_i);
    }
}

float MainWindow::calcEpsilon(int r)
{
    int i = 0, val;
    do
    {
        val = pow(2,i);
        i++;
    }while(val<r);
    float epsilon = 1/pow(2,i-1);
    return epsilon;
}

void MainWindow::drawCircleDDA(int xc, int yc, int rad)
{
    QRgb value;
    value = qRgb(0,255,0);

    int st_x = rad, st_y = 0;
    float x = st_x, y = st_y;
    float x1, y1;

    float epsilon = calcEpsilon(rad);
    do
    {
        x1 = x + epsilon*y;
        y1 = y - epsilon*x1;
        image.setPixel(int(xc + x1), int(yc - y1), value);
        x = x1; y = y1;
    }while((y - st_y) < epsilon || (st_x-x) > epsilon);
}
