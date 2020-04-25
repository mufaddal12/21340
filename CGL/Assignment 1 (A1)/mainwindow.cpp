#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
const int win_x = 500;
const int win_y = 500;

QImage image(win_x, win_y, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(OnClickedPushButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DDA_clicked(bool check)
{
    int x1, y1, x2, y2;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();
    drawLineDDA(x1,y1,x2,y2);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_BRES_clicked(bool check)
{
    int x1, y1, x2, y2;
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();
    drawLineBRES(x1,y1,x2,y2);
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
    /*QLabel l;
    l.setPixmap(QPixmap::fromImage(image));
    l.show();*/
}


void MainWindow::drawLineDDA(int x1, int y1, int x2, int y2)
{
    QRgb value;
    value = qRgb(0,255,255);

    /*for(int x = x1, y = y1;x<=x2; x++, y++)
    {
        image.setPixel(x,y,value);
    }*/
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

void MainWindow::drawLineBRES(int x1, int y1, int x2, int y2)
{
    QRgb value;
    value = qRgb(0,255,0);
    int x = x1;
    int y = y1;
    int delta_x = abs(x2-x1);
    int delta_y = abs(y2 - y1);

    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);

    int interchange = 0;
    if(delta_y > delta_x)
    {
        int temp = delta_x;
        delta_x = delta_y;
        delta_y = temp;

        interchange = 1;
    }

    int e_bar = 2 *delta_y - delta_x;
    for(int i = 1; i<=delta_x; i++)
    {
        image.setPixel(x, y, value);
        while(e_bar>0)
        {
            if(interchange)
                x = x + s1;
            else
                y = y + s2;
            e_bar = e_bar - 2*delta_x;
        }

        if(interchange)
            y = y + s2;
        else
            x = x + s1;
        e_bar = e_bar + 2*delta_y;
    }
}
