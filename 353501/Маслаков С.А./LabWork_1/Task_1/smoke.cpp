#include "smoke.h"
#include <QPainter>
Smoke::Smoke()
{
}

QRectF Smoke::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}

void Smoke::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(Qt::gray);
    painter->drawEllipse(boundingRect());
}



