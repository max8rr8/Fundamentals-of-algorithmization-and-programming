#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "locomotive.h"
#include "smoke.h"
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene * scene;
private slots:
    void start_movel();
    void stop_movel();
    void movel();
    void mover();
    void start_mover();
    void stop_mover();
    void move_smoke();
private:
    double currentvalue;
    double targetvalue;
    Ui::MainWindow *ui;
    Locomotive * rectangle;
    Smoke* smoke;
    QTimer* timer;
    QTimer* smoketimer;
};
#endif // MAINWINDOW_H
