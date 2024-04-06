#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include "locomotive.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    rectangle = new Locomotive();
    smoke = new Smoke();
    scene->addItem(rectangle);
    timer = new QTimer();
    smoketimer = new QTimer;
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    connect(ui->lef_button, &QPushButton::pressed, this, &MainWindow::start_movel);
    connect(ui->lef_button, &QPushButton::released, this, &MainWindow::stop_movel);
    connect(ui->righ_button, &QPushButton::pressed, this, &MainWindow::start_mover);
    connect(ui->righ_button, &QPushButton::released, this, &MainWindow::stop_mover);
    connect(smoketimer, &QTimer::timeout,this,&MainWindow::move_smoke);
}

void MainWindow::start_movel(){
    connect(timer, &QTimer::timeout, this, &MainWindow::movel);
    smoketimer->start(500);
    timer->start(30);
}

void MainWindow::movel(){
    if (rectangle->pos().x() < - 400){
       stop_movel();
    }
    else rectangle->moveleft();
}

void MainWindow::stop_movel(){
    disconnect(timer, &QTimer::timeout, this, &MainWindow::movel);
    timer->stop();
    smoketimer->stop();
}
void MainWindow::start_mover(){
    connect(timer, &QTimer::timeout, this, &MainWindow::mover);
    smoketimer->start(500);
    timer->start(30);
}

void MainWindow::mover(){
    if (rectangle->pos().x() + rectangle->boundingRect().width() > scene->width()) {
        stop_mover();
    }
   else rectangle->moveright();
}

void MainWindow::stop_mover(){
    disconnect(timer, &QTimer::timeout, this, &MainWindow::mover);
    timer->stop();
    smoketimer->stop();
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::move_smoke(){
    rectangle->emitSmoke();
}
