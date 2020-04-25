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
    int sign(float);
    void drawLineBRES(int x1, int y1, int x2, int y2);
private slots:
    void on_DDA_clicked(bool checked);
    void on_BRES_clicked(bool check);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
