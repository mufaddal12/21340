#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QVector>

namespace Ui {
class Polygon;
class MainWindow;
}

class Point
{
public:
    Point(int h=0,int k=0)
    {
        x=h;
        y=k;
    }

    int x, y;
};

class Polygon
{

    QVector<Point> allPoints;
    int vertices;
    Polygon(int n =0)
    {
        vertices = 0;
    }
    void addPoint(Point p)
    {
        allPoints.push_back(p);
        vertices++;
    }
    Point getTop()
    {
        if(vertices)
            return allPoints[vertices-1];
        else
        {
            Point p;
            return p;
        }
    }

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
    void on_pushButton_clicked();
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    Ui::MainWindow *ui;
    void drawLineDDA(Point p1, Point p2, QRgb value = qRgb(0,255,255));
};

#endif // MAINWINDOW_H
