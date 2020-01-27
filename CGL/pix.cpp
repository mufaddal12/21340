#include "pix.h"
#include "ui_pix.h"
#include<QApplication>
#include<QtGui>
#include<QLabel>
static QImage img(300,300,QImage::Format_RGB888);
Pix::Pix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pix)
{
    ui->setupUi(this);
}

Pix::~Pix()
{
    delete ui;
}

void Pix::on_pushButton_clicked()
{
    QRgb val;
    val=qRgb(255,0,0);
    int x=50,y=50;
     img.setPixel(200,100,qRgb(0,255,0));
    while(x<=200)
    {
    img.setPixel(x,y,val);
    x++;
    }
   ui->label->setPixmap(QPixmap::fromImage(img));

}
