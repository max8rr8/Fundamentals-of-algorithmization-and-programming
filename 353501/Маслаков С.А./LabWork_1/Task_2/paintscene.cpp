#include "paintscene.h"

paintscene::paintscene(QObject* parent) : QGraphicsScene(parent) , holdmouse(false){}

void paintscene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        holdmouse = true;
        emit mousePressed(event->scenePos());
    }

    QGraphicsScene::mousePressEvent(event);
}

void paintscene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        holdmouse = false;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void paintscene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (holdmouse)
    {
        emit mousePressed(event->scenePos());
    }

    QGraphicsScene::mouseMoveEvent(event);
}
\
