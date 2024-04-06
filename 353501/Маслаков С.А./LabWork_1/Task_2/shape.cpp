#include "shape.h"
void Shape::number_apexes(int number){}

void Shape::paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    QPolygonF polygon;
    QPointF rotationCenter;
    calculate_points();
    rotationCenter = (QPointF(0 + X, 0 + Y));
    if(!center_connected) {
        rotationCenter = (QPointF(0 + rotatecenterx, 0 + rotatecentery));
    }
    painter->setRenderHint(QPainter::Antialiasing);
    move = {X,Y};
    painter->translate(rotationCenter);
    painter->rotate(rotate_angle);
    painter->translate(-rotationCenter);
    for(auto &point : points){
        polygon << point * scale + move;
    }
    painter->drawPolygon(polygon);
    painter->drawEllipse(rotationCenter,1,1);
}
void Shape::centerset(){
    centerx = 0;
    centery = 0;
    int n = points.size();
    for(int i = 0;i < n;++i){
        centerx += pointsx[i] / n;
        centery += pointsy[i] / n;
    }
    for(int i = 0;i < n;++i){
        points[i] -= {centerx,centery};
    }

}
QRectF Shape::boundingRect() const{
    return QRectF();
}
void Shape::changescale(double spinscale){
    scale = spinscale;
}
void Shape::changerad(double spinrad){
    radius = spinrad;
}
void Shape::move_x(double spinX){
    X = spinX;
}
void Shape::move_y(double spinY){
    Y = spinY;
}
void Shape::rotate(double spinangle){
    rotate_angle = spinangle;
}
void Shape::changerotatecenterx(double spincoordx){
    rotatecenterx = spincoordx;
}
void Shape::changerotatecentery(double spincoordy){
    rotatecentery = spincoordy;
}
qreal Shape::perimeter(){}
qreal Shape::area(){}
void Shape::calculate_points(){}
