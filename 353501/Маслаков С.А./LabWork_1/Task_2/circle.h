#ifndef CIRCLE_H
#define CIRCLE_H


#include "shape.h"
#include "QPainter"

class Circle : public Shape
{
    Q_OBJECT

public:
    QPointF center;
    Circle() = default;
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    qreal area() override;
    qreal perimeter() override;
};

#endif // CIRCLE_H
