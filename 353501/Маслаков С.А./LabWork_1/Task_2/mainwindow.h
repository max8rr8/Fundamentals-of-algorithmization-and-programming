#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QGraphicsScene>
#include <QTimer>
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "star.h"
#include "right_polygone.h"
#include "rhombus.h"
#include "square.h"
#include "custom_shape.h"
#include "paintscene.h"
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

private slots:
    void changexstart(double value);
    void changexhandler();
    void changexcomplete();
    void changeystart(double value);
    void changeyhandler();
    void changeycomplete();
    void changescalestart(double value);
    void changescalehandler();
    void changescalecomplete();
    void change_rotation_start(double value);
    void change_rotation_handler();
    void change_rotation_complete();
    void change_rotationcenterx_start(double value);
    void change_rotationcenterx_handler();
    void change_rotationcenterx_complete();
    void change_rotationcentery_start(double value);
    void change_rotationcentery_handler();
    void change_rotationcentery_complete();
    void when_mousepressed(const QPointF &position);
    void on_comboBox_activated(int index);
    //void on_scalespinbox_valueChanged(double arg1);
    void on_radiusSpinBox_valueChanged(double arg1);
    //void on_changeyspinbox_valueChanged(double arg1);
    //void on_cahgexspinbox_valueChanged(double arg1);

    void on_side1trianglespin_valueChanged(double arg1);

    void on_side2trianglespin_valueChanged(double arg1);

    void on_side3trianglespin_valueChanged(double arg1);

    //void on_rotationspinbox_valueChanged(double arg1);

    void on_heightrectspinbox_valueChanged(double arg1);

    void on_widthrectspinbox_valueChanged(double arg1);

    void on_apexes_spinbox_valueChanged(int arg1);

    void on_radius1_spinbox_valueChanged(double arg1);

    void on_radius2_spinbox_valueChanged(double arg1);

    void on_spinboxnumapexes_rp_valueChanged(int arg1);

    void on_spinboxside_rd_valueChanged(double arg1);

    void on_spinbox_angle_rh_valueChanged(double arg1);

    void on_spinbox_side_rh_valueChanged(double arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    //void on_doubleSpinBox_2_valueChanged(double arg1);

    //void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_radioButton_toggled(bool checked);

    void on_pushButton_clicked();

private:
    bool paintchoose = false;
    QTimer * timer;
    Ui::MainWindow *ui;
    paintscene * scene;
    Circle* circle;
    Triangle* triangle;
    Rectangle* rectangle;
    Star* star;
    Right_Polygone* right_polygone;
    Rhombus* rhombus;
    Custom_shape* custom;
    Square* square;
    Shape* shapes_arr[10];
    int shape_index = 0;
    double targetvalue;
    double currenttvalue;
protected:
    void set_info();
};
#endif // MAINWINDOW_H
