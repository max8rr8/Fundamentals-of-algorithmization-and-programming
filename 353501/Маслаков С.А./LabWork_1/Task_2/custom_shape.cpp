#include "custom_shape.h"

Custom_shape::Custom_shape(){}
void Custom_shape::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(QPen(Qt::black, 2));
    QPointF rotationCenter;
    rotationCenter = (QPointF(0 + X, 0 + Y));
    if(!center_connected) {
        rotationCenter = (QPointF(0 + rotatecenterx, 0 + rotatecentery));
    }
    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(rotationCenter);
    painter->rotate(rotate_angle);
    painter->translate(-rotationCenter);
    for (int i = 0; i < points.size();++i) {
        painter->drawEllipse(points[i] * scale + QPointF(X,Y),1,1);
    }
    painter->drawEllipse(rotationCenter,1,1);
}

void Custom_shape::addPoint(const QPointF& point)
{
    points.push_back(point);
}
