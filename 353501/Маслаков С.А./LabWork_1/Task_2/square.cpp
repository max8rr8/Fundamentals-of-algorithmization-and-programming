#include "square.h"

Square::Square() {}
void Square::calculate_points() {
    points.resize(4);
    pointsx.resize(4);
    pointsy.resize(4);

    pointsx[0] = 0;
    pointsy[0] = 0;

    pointsx[1] = side;
    pointsy[1] = 0;

    pointsx[2] = side;
    pointsy[2] = side;

    pointsx[3] = 0;
    pointsy[3] = side;

    for (int i = 0; i < 4; ++i) {
        points[i] = QPointF(pointsx[i], pointsy[i]);
    }
    centerset();
}
qreal Square::area(){
    return side * side;
}
qreal Square::perimeter(){
    return side * 4;
}
void Square::change_side(double spinside){
    side = spinside;
    calculate_points();
}
