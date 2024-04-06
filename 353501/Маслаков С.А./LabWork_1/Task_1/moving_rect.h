#ifndef MOVING_RECT_H
#define MOVING_RECT_H
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include <QPointF>
class Moving_rect : public QGraphicsRectItem, public QObject
{
public:
    Moving_rect();
    QRectF boundingRect() const override;
    int x = -200;
    QPointF coordinates;
private:

public slots:
    void moveleft();
    void moveright();

};
#endif // MOVING_RECT_H
