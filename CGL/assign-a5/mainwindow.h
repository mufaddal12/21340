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

private:
    Ui::MainWindow *ui;
    void drawLine(int x1, int y1, int x2, int y2, QRgb value = qRgb(255,255,255));
    void drawFig(int side);
};

#endif // MAINWINDOW_H
