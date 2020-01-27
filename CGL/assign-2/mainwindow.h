#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawLineDDA(int x1, int y1, int x2, int y2);
    void mh(int &xi, int &delta_i);
    void mv(int &yi, int &delta_i);
    void md(int &xi, int &yi, int &delta_i);
    void drawCircleBRES(int xc, int yc, int rad);
    void drawCircleDDA(int xc, int yc, int rad);
    float calcEpsilon(int r);
    int sign(float);
public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;/*
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked(bool checked);
    void on_pushButton_3_clicked(bool checked);*/
};

#endif // MAINWINDOW_H
