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
    void on_solid_clicked();

    void on_dashed_clicked();

    void on_dotted_clicked();

    void on_dashDot_clicked();

    void on_thick_clicked();

private:
    Ui::MainWindow *ui;
    void drawSolidLine(int x1, int y1, int x2, int y2, QRgb value = qRgb(0,255,255));
    void drawDottedLine(int x1, int y1, int x2, int y2, QRgb value = qRgb(255,255,255));
    void drawDashedLine(int x1, int y1, int x2, int y2, QRgb value = qRgb(255,0,0));
    void drawDashDotLine(int x1, int y1, int x2, int y2, QRgb value = qRgb(255,255,0));
    void drawThickLine(int x1, int y1, int x2, int y2, QRgb value = qRgb(255,0,255));
};

#endif // MAINWINDOW_H
