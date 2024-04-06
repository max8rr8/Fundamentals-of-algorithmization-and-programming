#ifndef RHOMBUS_H
#define RHOMBUS_H
#include "shape.h"
class Rhombus : public Shape
{
    double side = 100;
    double angle = 60;
public:
    qreal area() override;
    qreal perimeter() override;
    void change_side(double spinside);
    void changeangle(double spinangle);
    void calculate_points() override;
    Rhombus();
};

#endif // RHOMBUS_H
