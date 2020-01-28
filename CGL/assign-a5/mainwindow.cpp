#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
const int win_x = 500;
const int win_y = 500;

const float const_topx = win_x/2;
const float const_topy = 20;

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
    //connect(ui->pushButsideton, SIGNAL(clicked()), this, SLOT(OnClickedPushButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_draw_clicked()
{
    int side = ui->side->toPlainText().toInt();
    drawChessBoard(side);
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::drawChessBoard(float side)
{
    side = side/sqrt(2);
    float topy, topx_right, topx_left;
    float leftx, rightx, boty;
    float unitsq = side/4;
    for(int i = 0; i<5; i++)
    {
        topx_right = const_topx + i*unitsq;
        topx_left = const_topx - i*unitsq;
        topy = const_topy + i*unitsq;

        leftx = topx_right - side;
        rightx = topx_left + side;

        boty = topy + side;

        drawLine(topx_right, topy, leftx, boty);
        drawLine(topx_left, topy, rightx, boty);
    }
}

void MainWindow::drawLine(float x1, float y1, float x2, float y2, QRgb value)
{
    float x = x1;
    float y = y1;
    float delta_x = abs(x2-x1);
    float delta_y = abs(y2 - y1);

    float s1 = sign(x2 - x1);
    float s2 = sign(y2 - y1);

    float interchange = 0;
    if(delta_y > delta_x)
    {
        float temp = delta_x;
        delta_x = delta_y;
        delta_y = temp;

        interchange = 1;
    }

    float e_bar = 2 *delta_y - delta_x;
    for(int i = 0; i<=delta_x; i++)
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


void MainWindow::on_fill_clicked()
{
    int side = ui->side->toPlainText().toInt();
    float unitsq = side/4;

    float topy = const_topy + unitsq;
   // float topx_right = const_topx;
    float topx_left = const_topx;

    //for(int i = 0; i<4; i++)
    {
        floodFill(topx_left, topy);
    }

}

void MainWindow::floodFill(int x, int y, QRgb bgColour, QRgb fillColour)
{
    QRgb val = image.pixel(x,y);
    if(val != bgColour)
        return;
    image.setPixel(x,y,fillColour);
    floodFill(x+1,y, bgColour, fillColour);
    floodFill(x-1,y, bgColour, fillColour);
    floodFill(x,y+1, bgColour, fillColour);
    floodFill(x,y-1, bgColour, fillColour);
}







