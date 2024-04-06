#include "triangle.h"

Triangle::Triangle() {}
void Triangle::calculate_points(){
    points.resize(3);
    pointsy.resize(3);
    pointsx.resize(3);
    pointsx[0] = 0;
    pointsy[0] = 0;
    pointsx[1] = side1;
    pointsy[1] = 0;
    pointsx[2] = (side3*side3 + side1*side1 - side2*side2) / (2.0 * side1);
    pointsy[2] = sqrt(side3*side3 - pow((side3*side3 + side1*side1 - side2*side2) / (2.0 * side1), 2));

    points[0] = QPointF(pointsx[0], pointsy[0]);
    points[1] = QPointF(pointsx[1], pointsy[1]);
    points[2] = QPointF(pointsx[2], pointsy[2]);
    centerset();
}
//void Triangle::paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){}
qreal Triangle::area(){
    double p = (side1 + side2 + side3) / 2;
    return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}
qreal Triangle::perimeter(){
    return side1 + side2 + side3;
}
void Triangle::change_side1(double spinside1){
    side1 = spinside1;
    calculate_points();
}
void Triangle::change_side2(double spinside2){
    side2 = spinside2;
    calculate_points();
}
void Triangle::change_side3(double spinside3){
    side3 = spinside3;
    calculate_points();
}

