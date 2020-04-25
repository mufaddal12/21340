#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class Point;
class Polygon;
class MainWindow;
}

class Point;

class Matrix
{
    QVector<QVector<float>> mat;
    int m, n;
public:
    Matrix(int r = 0, int c = 0)
    {
        m = r;
        n = c;
        for(int i = 0; i<m; i++)
        {
            QVector<float> row;
            for(int j = 0; j<n; j++)
            {
                row.push_back(0);
            }
            mat.push_back(row);
        }
    }
    void addRow(QVector<float> row){mat.push_back(row); n = row.size(); m++;}
    void addRow(Point p);
    void clear(){mat.clear(); m=n=0;}
    int rows() {return m;}
    int cols(){return n;}
    QVector<float> getRow(int i){return mat[i];}
    Matrix operator *(const Matrix A);
    Matrix operator +(const Matrix A);
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
    Matrix allPoints;
    QRgb lineColour;
    int vertices;
public:
    Polygon()
    {
        vertices = 0;
        lineColour = qRgb(255,255,255);
    }
    Polygon(Matrix m)
    {
        allPoints = m;
        vertices = m.rows();
    }
    void addVertex(Point p);
    Point getFront();
    Point getRear();
    Point getPoint(int i);
    bool isEmpty();
    void clearPoly();
    void scale(float, float);
    void rotate(int theta, int x=-1, int y=-1);
    void translate(int x, int y);
    void reflectAboutX();
    void getNextHilbert();
    void display(int x = 0,int y = 0);
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

    void on_input_clicked();

    void on_next_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
