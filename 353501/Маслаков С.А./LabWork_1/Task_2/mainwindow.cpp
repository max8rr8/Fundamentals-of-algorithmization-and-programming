#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    scene = new paintscene(this);
    ui->graphicsView->setScene(scene);
    timer = new QTimer(this);
    circle = new Circle();
    triangle = new Triangle();
    rectangle = new Rectangle();
    star = new Star();
    rhombus = new Rhombus();
    square = new Square();
    right_polygone = new Right_Polygone();
    custom = new Custom_shape();
    shapes_arr[0] = circle;
    shapes_arr[1] = triangle;
    shapes_arr[2] = rectangle;
    shapes_arr[3] = star;
    shapes_arr[4] = right_polygone;
    shapes_arr[5] = rhombus;
    shapes_arr[6] = square;
    shapes_arr[7] = custom;
    ui->rotate_frame->hide();
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    connect(ui->comboBox, &QComboBox::activated,ui->frames, &QStackedWidget::setCurrentIndex);
    connect(scene, &paintscene::mousePressed, this, &MainWindow::when_mousepressed);
    connect(ui->cahgexspinbox,&QDoubleSpinBox::valueChanged,this,&MainWindow::changexstart);
    connect(ui->changeyspinbox,&QDoubleSpinBox::valueChanged,this,&MainWindow::changeystart);
    connect(ui->scalespinbox,&QDoubleSpinBox::valueChanged,this,&MainWindow::changescalestart);
    connect(ui->rotationspinbox,&QDoubleSpinBox::valueChanged,this,&MainWindow::change_rotation_start);
    connect(ui->rotationcenterxspinbox,&QDoubleSpinBox::valueChanged,this,&MainWindow::change_rotationcenterx_start);
    connect(ui->rotationcenteryspinbox,&QDoubleSpinBox::valueChanged,this,&MainWindow::change_rotationcentery_start);
    ui->frames->hide();
}

void MainWindow::on_comboBox_activated(int index)
{
    if(index == 7){
        ui->area_label->hide();
        ui->perimeter_label->hide();
        ui->text_label2->hide();
        ui->text_label3->hide();
        paintchoose = true;
        ui->Changeframe->hide();
    }
    else {
        ui->area_label->show();
        ui->perimeter_label->show();
        ui->text_label2->show();
        ui->text_label3->show();
    }
    scene->removeItem(shapes_arr[shape_index]);
    shape_index = index;
    scene->addItem(shapes_arr[shape_index]);
    ui->graphicsView->viewport()->update();
    ui->frames->show();
    ui->spinbox_angle_rh->setValue(60);
    ui->changeyspinbox->setValue(0);
    ui->cahgexspinbox->setValue(0);
    ui->rotationspinbox->setValue(0);
    ui->scalespinbox->setValue(0);
    shapes_arr[shape_index]->X = 0;
    shapes_arr[shape_index]->Y = 0;
    shapes_arr[shape_index]->rotate_angle = 0;
    shapes_arr[shape_index]->scale = 1;
    set_info();
}
//change scale for all shapes
//void MainWindow::on_scalespinbox_valueChanged(double arg1)
//{
    //shapes_arr[shape_index]->changescale(arg1);
    //ui->graphicsView->viewport()->update();
//}
//circlespinbox for rad
void MainWindow::on_radiusSpinBox_valueChanged(double arg1)
{

    shapes_arr[shape_index]->changerad(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}

void MainWindow::set_info()
{
    ui->area_label->setText(QString::number(shapes_arr[shape_index]->area()));
    ui->perimeter_label->setText(QString::number(shapes_arr[shape_index]->perimeter()));
}
//void MainWindow::on_changeyspinbox_valueChanged(double arg1)
//{
    //shapes_arr[shape_index]->move_y(arg1);
    //ui->graphicsView->viewport()->update();
//}
//void MainWindow::on_cahgexspinbox_valueChanged(double arg1)
//{
    //shapes_arr[shape_index]->move_x(arg1);
    //ui->graphicsView->viewport()->update();
//}

MainWindow::~MainWindow()
{
    delete ui;
}
//animation spinx
//move x
void MainWindow::changexstart(double value)
{
    currenttvalue = shapes_arr[shape_index]->X;
    targetvalue = value;
    connect(timer,&QTimer::timeout,this,&MainWindow::changexhandler);
    timer->start(10);
}
void MainWindow::changexhandler(){
    if(currenttvalue < targetvalue){
        currenttvalue++;
        shapes_arr[shape_index]->move_x(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else if(currenttvalue > targetvalue){
        currenttvalue--;
        shapes_arr[shape_index]->move_x(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else{
        changexcomplete();
    }
}
void MainWindow::changexcomplete(){
    disconnect(timer, &QTimer::timeout, this, &MainWindow::changexhandler);
    timer->stop();
}
//move y
void MainWindow::changeystart(double value)
{
    currenttvalue = shapes_arr[shape_index]->Y;
    targetvalue = value;
    connect(timer,&QTimer::timeout,this,&MainWindow::changeyhandler);
    timer->start(10);
}
void MainWindow::changeyhandler(){
    if(currenttvalue < targetvalue){
        currenttvalue++;
        shapes_arr[shape_index]->move_y(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else if(currenttvalue > targetvalue){
        currenttvalue--;
        shapes_arr[shape_index]->move_y(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else{
        changeycomplete();
    }
}
void MainWindow::changeycomplete(){
    disconnect(timer, &QTimer::timeout, this, &MainWindow::changeyhandler);
    timer->stop();
}
//scale change
void MainWindow::changescalestart(double value)
{
    currenttvalue = shapes_arr[shape_index]->scale;
    targetvalue = value;
    connect(timer,&QTimer::timeout,this,&MainWindow::changescalehandler);
    timer->start(10);
}
void MainWindow::changescalehandler(){
    if(currenttvalue < targetvalue){
        currenttvalue += 0.25;
        shapes_arr[shape_index]->changescale(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else if(currenttvalue > targetvalue){
        currenttvalue -= 0.25;
        shapes_arr[shape_index]->changescale(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else{
        changescalecomplete();
    }
}
void MainWindow::changescalecomplete(){
    disconnect(timer, &QTimer::timeout, this, &MainWindow::changescalehandler);
    timer->stop();
}
//rotation animation
void MainWindow::change_rotation_start(double value)
{
    currenttvalue = shapes_arr[shape_index]->rotate_angle;
    targetvalue = value;
    connect(timer,&QTimer::timeout,this,&MainWindow::change_rotation_handler);
    timer->start(10);
}
void MainWindow::change_rotation_handler(){
    if(currenttvalue < targetvalue){
        currenttvalue++;
        shapes_arr[shape_index]->rotate(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else if(currenttvalue > targetvalue){
        currenttvalue--;
        shapes_arr[shape_index]->rotate(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else{
        change_rotation_complete();
    }
}
void MainWindow::change_rotation_complete(){
    disconnect(timer, &QTimer::timeout, this, &MainWindow::change_rotation_handler);
    timer->stop();
}
//rotation center x
void MainWindow::change_rotationcenterx_start(double value)
{
    currenttvalue = shapes_arr[shape_index]->rotatecenterx;
    targetvalue = value;
    connect(timer,&QTimer::timeout,this,&MainWindow::change_rotationcenterx_handler);
    timer->start(10);
}
void MainWindow::change_rotationcenterx_handler(){
    if(currenttvalue < targetvalue){
        currenttvalue++;
        shapes_arr[shape_index]->changerotatecenterx(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else if(currenttvalue > targetvalue){
        currenttvalue--;
        shapes_arr[shape_index]->changerotatecenterx(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else{
        change_rotationcenterx_complete();
    }
}
void MainWindow::change_rotationcenterx_complete(){
    disconnect(timer, &QTimer::timeout, this, &MainWindow::change_rotationcenterx_handler);
    timer->stop();
}
//rotate center y
void MainWindow::change_rotationcentery_start(double value)
{
    currenttvalue = shapes_arr[shape_index]->rotatecentery;
    targetvalue = value;
    connect(timer,&QTimer::timeout,this,&MainWindow::change_rotationcentery_handler);
    timer->start(10);
}
void MainWindow::change_rotationcentery_handler(){
    if(currenttvalue < targetvalue){
        currenttvalue++;
        shapes_arr[shape_index]->changerotatecentery(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else if(currenttvalue > targetvalue){
        currenttvalue--;
        shapes_arr[shape_index]->changerotatecentery(currenttvalue);
        ui->graphicsView->viewport()->update();
        set_info();
    }
    else{
        change_rotationcentery_complete();
    }
}
void MainWindow::change_rotationcentery_complete(){
    disconnect(timer, &QTimer::timeout, this, &MainWindow::change_rotationcentery_handler);
    timer->stop();
}
//triangle frame
void MainWindow::on_side1trianglespin_valueChanged(double arg1)
{
    triangle->change_side1(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_side2trianglespin_valueChanged(double arg1)
{
    triangle->change_side2(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_side3trianglespin_valueChanged(double arg1)
{
    triangle->change_side3(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


//void MainWindow::on_rotationspinbox_valueChanged(double arg1)
//{
    //shapes_arr[shape_index]->rotate(arg1);
    //ui->graphicsView->viewport()->update();
//}


void MainWindow::on_heightrectspinbox_valueChanged(double arg1)
{
    rectangle->change_height(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_widthrectspinbox_valueChanged(double arg1)
{
    rectangle->change_width(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}

void MainWindow::on_apexes_spinbox_valueChanged(int arg1)
{
    star->number_apexes(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_radius1_spinbox_valueChanged(double arg1)
{
    star->change_radius1(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_radius2_spinbox_valueChanged(double arg1)
{
    star->change_radius2(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}



void MainWindow::on_spinboxnumapexes_rp_valueChanged(int arg1)
{
    right_polygone->number_apexes(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_spinboxside_rd_valueChanged(double arg1)
{
    right_polygone->change_side(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_spinbox_angle_rh_valueChanged(double arg1)
{
    rhombus->changeangle(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_spinbox_side_rh_valueChanged(double arg1)
{
    rhombus->change_side(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    square->change_side(arg1);
    ui->graphicsView->viewport()->update();
    set_info();
}


//void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1) //for centerx
//{
    //shapes_arr[shape_index]->changerotatecenterx(arg1);
    //ui->graphicsView->viewport()->update();
//}


//void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1) //for centery
//{
    //shapes_arr[shape_index]->changerotatecentery(arg1);
    //ui->graphicsView->viewport()->update();
//}


void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked){
        shapes_arr[shape_index]->center_connected = true;
        ui->rotate_frame->hide();
    }
    else{
        shapes_arr[shape_index]->center_connected = false;
        ui->rotate_frame->show();
    }
    ui->graphicsView->viewport()->update();
}
void MainWindow::when_mousepressed(const QPointF &position){
    if(paintchoose){
    custom->addPoint(position);
    ui->graphicsView->viewport()->update();
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->Changeframe->show();
}

