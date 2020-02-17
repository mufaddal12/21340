#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QVector>

namespace Ui {
class Point;
class Polygon;
class MainWindow;
}

class Point
{
    int px, py;
public:
    Point(int h=0,int k=0)
    {
        px=h;
        py=k;
    }
    int x(){return px;}
    int y(){return py;}
    bool range(int x, int y, int offset_x, int offset_y);
    void addOffset(int, int);
    friend class Polygon;
};

class Polygon
{
    QVector<Point> allPoints;
    int vertices;
    QRgb fillColour;
public:
    Polygon()
    {
        vertices = 0;
        fillColour = qRgb(0,0,0);
    }
    void addVertex(Point p);
    Point getFront();
    Point getRear();
    bool isEmpty();
    void clearPoly();
    void changeColour(int, int, int);
    friend void seedFill(int, int, QRgb, QRgb);
    friend class MainWindow;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Polygon poly;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void on_clear_clicked();

    void on_red_valueChanged(int value);

    void on_green_valueChanged(int value);

    void on_blue_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    void changeDisplay(int r, int g, int b);
};

#endif // MAINWINDOW_H
