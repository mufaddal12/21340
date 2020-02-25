#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

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
    void change(int, int);
    friend class Polygon;
};

class Polygon
{
    QVector<Point> allPoints;
    QVector<QMap<char, bool>> bools;
    int vertices;
public:
    Polygon()
    {
        vertices = 0;

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
    Polygon actualPoly;
    Point A, B, C, D;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent *m);

private:
    Ui::MainWindow *ui;
    void changeViewPoly(Point p);
};

#endif // MAINWINDOW_H
