#ifndef RIGHT_POLYGONE_H
#define RIGHT_POLYGONE_H
#include "shape.h"
class Right_Polygone : public Shape
{
    int side = 50;
    int apexes_num = 4;
public:
    Right_Polygone();
    void number_apexes(int number) override;
    qreal area() override;
    qreal perimeter() override;
    void change_side(double spinside);
    void calculate_points() override;
};

#endif // RIGHT_POLYGONE_H
