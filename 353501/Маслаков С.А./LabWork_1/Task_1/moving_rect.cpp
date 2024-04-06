#include "moving_rect.h"

Moving_rect::Moving_rect() : QGraphicsRectItem(){
    coordinates = pos();
}

void Moving_rect::moveleft(){
    x -= 2;
    coordinates.setX(x);
    setPos(coordinates);
}
void Moving_rect::moveright(){
    x += 3;
    coordinates.setX(x);
    setPos(coordinates);
}
QRectF Moving_rect::boundingRect() const{
    return QRectF();
}


