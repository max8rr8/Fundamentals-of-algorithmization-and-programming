#include "circle.h"

void Circle::paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPointF rotationCenter;
    rotationCenter = (QPointF(0 + X, 0 + Y));
    if(!center_connected) {
        rotationCenter = (QPointF(0 + rotatecenterx, 0 + rotatecentery));
    }
    center = {0 + X,0 + Y};
    painter->translate(rotationCenter);
    painter->rotate(rotate_angle);
    painter->translate(-rotationCenter);
    painter->drawEllipse(center,radius * scale,radius * scale);
    painter->drawEllipse(rotationCenter,1,1);
}
qreal Circle::area(){
    return M_PI * (radius * radius);
}
qreal Circle::perimeter(){
    return 2 * M_PI * radius;
}
