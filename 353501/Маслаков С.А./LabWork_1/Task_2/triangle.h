#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"

class Triangle : public Shape
{
    double side1 = 50;
    double side2 = 50;
    double side3 = 50;

public:
    //void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    qreal area() override;
    qreal perimeter() override;
    void change_side1(double spinside1);
    void change_side2(double spinside2);
    void change_side3(double spinside3);
    void calculate_points() override;
    Triangle();
};

#endif // TRIANGLE_H
