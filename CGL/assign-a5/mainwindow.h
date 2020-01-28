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

private slots:
    void on_draw_clicked();

    void on_fill_clicked();

private:
    Ui::MainWindow *ui;
    int y;
    void drawLine(float x1, float y1, float x2, float y2, QRgb value = qRgb(255,255,255));
    void drawChessBoard(float side);
    void floodFill(int x, int y, QRgb bgColour = qRgb(0,0,0), QRgb fillColour = qRgb(255,255,255));
};

#endif // MAINWINDOW_H
