#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
const int win_x = 500;
const int win_y = 500;

QImage image(win_x, win_y, QImage::Format_RGB888);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_solid_clicked()
{
    int x1, y1, x2, y2;
    x1 = ui->x1->toPlainText().toInt();
    y1 = ui->y1->toPlainText().toInt();
    x2 = ui->x2->toPlainText().toInt();
    y2 = ui->y2->toPlainText().toInt();
    drawSolidLine(x1,y1,x2,y2);
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::drawSolidLine(int x1, int y1, int x2, int y2, QRgb value)
{
   // QRgb value = qRgb(0,255,255);
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

void MainWindow::on_dotted_clicked()
{
    int x1, y1, x2, y2;
    x1 = ui->x1->toPlainText().toInt();
    y1 = ui->y1->toPlainText().toInt();
    x2 = ui->x2->toPlainText().toInt();
    y2 = ui->y2->toPlainText().toInt();
    drawDottedLine(x1,y1,x2,y2);
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::drawDottedLine(int x1, int y1, int x2, int y2, QRgb value)
{
   // QRgb value = qRgb(0,255,255);
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
        if(i%2)
            image.setPixel(int(floor(x)),int(floor(y)), value);
        x = x + delta_x;
        y = y + delta_y;
    }
}

void MainWindow::on_dashed_clicked()
{
    int x1, y1, x2, y2;
    x1 = ui->x1->toPlainText().toInt();
    y1 = ui->y1->toPlainText().toInt();
    x2 = ui->x2->toPlainText().toInt();
    y2 = ui->y2->toPlainText().toInt();
    drawDashedLine(x1,y1,x2,y2);
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::drawDashedLine(int x1, int y1, int x2, int y2, QRgb value)
{
   // QRgb value = qRgb(0,255,255);
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
        if(i%5)
            image.setPixel(int(floor(x)),int(floor(y)), value);
        x = x + delta_x;
        y = y + delta_y;
    }
}

void MainWindow::on_dashDot_clicked()
{
    int x1, y1, x2, y2;
    x1 = ui->x1->toPlainText().toInt();
    y1 = ui->y1->toPlainText().toInt();
    x2 = ui->x2->toPlainText().toInt();
    y2 = ui->y2->toPlainText().toInt();
    drawDashDotLine(x1,y1,x2,y2);
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::drawDashDotLine(int x1, int y1, int x2, int y2, QRgb value)
{
   // QRgb value = qRgb(0,255,255);
    int length;
    if(abs(x2-x1) > abs(y2-y1))
        length = abs(x2-x1);
    else
        length = abs(y2-y1);
    float delta_x = (x2-x1)/float(length);
    float delta_y = (y2-y1)/float(length);

    float x = x1 + 0.5*sign(delta_x);
    float y = y1 + 0.5*sign(delta_y);

    int k;
    int dash = 9;
    int space = 2;
    for(int i = 0; i< length; i++)
    {
        k = i%dash;
        if(k)
            if(k<dash-2*space || k==dash-space)
                image.setPixel(int(floor(x)),int(floor(y)), value);
        x = x + delta_x;
        y = y + delta_y;
    }
}

void MainWindow::on_thick_clicked()
{
    int x1, y1, x2, y2;
    x1 = ui->x1->toPlainText().toInt();
    y1 = ui->y1->toPlainText().toInt();
    x2 = ui->x2->toPlainText().toInt();
    y2 = ui->y2->toPlainText().toInt();
    int del_x = abs(x2-x1);
    int del_y = abs(y2-y1);
    drawThickLine(x1,y1,x2,y2);
    if(del_x < del_y)
    {
        drawThickLine(x1-1,y1,x2-1,y2);
        drawThickLine(x1+1,y1,x2+1,y2);
    }
    else
    {
        drawThickLine(x1,y1-1,x2,y2-1);
        drawThickLine(x1,y1+1,x2,y2+1);
    }
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::drawThickLine(int x1, int y1, int x2, int y2, QRgb value)
{
   // QRgb value = qRgb(0,255,255);
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

