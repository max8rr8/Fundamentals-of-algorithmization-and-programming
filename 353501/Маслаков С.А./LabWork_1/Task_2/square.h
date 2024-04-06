#ifndef SQUARE_H
#define SQUARE_H
#include "shape.h"
class Square : public Shape
{
    double side = 50;
public:
    qreal area() override;
    qreal perimeter() override;
    void calculate_points() override;
    void change_side(double spinside);
    Square();
};

#endif // SQUARE_H
