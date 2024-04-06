#include "rectangle.h"

Rectangle::Rectangle() {}
void Rectangle::calculate_points() {
    points.resize(4);
    pointsx.resize(4);
    pointsy.resize(4);

    pointsx[0] = 0;
    pointsy[0] = 0;

    pointsx[1] = width;
    pointsy[1] = 0;

    pointsx[2] = width;
    pointsy[2] = height;

    pointsx[3] = 0;
    pointsy[3] = height;

    for (int i = 0; i < 4; ++i) {
        points[i] = QPointF(pointsx[i], pointsy[i]);
    }
    centerset();
}
qreal Rectangle::area(){
    return height * width;
}
qreal Rectangle::perimeter(){
    return (height + width) * 2;
}
void Rectangle::change_height(double spinheight){
    height = spinheight;
    calculate_points();
}
void Rectangle::change_width(double spinwidth){
    width = spinwidth;
    calculate_points();
}
