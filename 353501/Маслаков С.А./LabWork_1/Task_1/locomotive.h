#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H
#include "moving_rect.h"
#include<QPainter>
#include<QGraphicsItem>
class Locomotive : public Moving_rect
{
public:
    Locomotive();
    void drawTube(QPainter* painter);
    void emitSmoke();
    QRectF tubeRect;
protected:
    void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

#endif // LOCOMOTIVE_H
