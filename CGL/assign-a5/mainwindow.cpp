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
    //connect(ui->pushButsideton, SIGNAL(clicked()), this, SLOT(OnClickedPushButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_draw_clicked()
{
    int side = ui->side->toPlainText().toInt();
    drawFig(side);
    ui->window->setPixmap(QPixmap::fromImage(image));
    ui->window->show();
}

void MainWindow::drawFig(int side)
{
    int topx = win_x/2;
    int topy = 1;
    float root2 = sqrt(2);
    float righty = topy + (1/root2)*side;
    float rightx = topx + (1/root2)*side;
    float lefty = topy + (1/root2)*side;
    float leftx = topx - (1/root2)*side;
    int botx = topx;
    float boty = lefty*2;
    drawLine(rightx, righty, topx, topy);
    drawLine(rightx, righty, botx-1, boty);
    drawLine(leftx, lefty, topx-1, topy);
    drawLine(leftx, lefty, botx, boty);
}

void MainWindow::drawLine(int x1, int y1, int x2, int y2, QRgb value)
{
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



