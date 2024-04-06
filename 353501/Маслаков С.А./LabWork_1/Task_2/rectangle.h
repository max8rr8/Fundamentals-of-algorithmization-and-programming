#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"
#include "QPolygon"
class Rectangle : public Shape
{
    double height = 50;
    double width = 100;
public:

    qreal area() override;
    qreal perimeter() override;
    void calculate_points() override;
    void change_height(double spinheight);
    void change_width(double spinwidth);
    Rectangle();
};

#endif // RECTANGLE_H
