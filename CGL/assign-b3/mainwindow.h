#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ClippingWin;
class Point;
class Polygon;
class MainWindow;
}

class ClippingWin
{
    int x1, y1, x2, y2;
};

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
public:
    Polygon()
    {
        vertices = 0;
        fillColour = qRgb(0,0,0);
        lineColour = qRgb(255,255,255);
    }
    void addVertex(Point p);
    Point getFront();
    Point getRear();
    bool isEmpty();
    void clearPoly();
    friend class MainWindow;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
