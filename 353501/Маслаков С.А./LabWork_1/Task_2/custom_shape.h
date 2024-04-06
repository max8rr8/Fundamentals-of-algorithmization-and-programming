#ifndef CUSTOM_SHAPE_H
#define CUSTOM_SHAPE_H

#include <QWidget>
#include "shape.h"
class Custom_shape : public Shape
{
    Q_OBJECT
public:
    Custom_shape();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void addPoint(const QPointF& point);
};

#endif // CUSTOM_SHAPE_H
