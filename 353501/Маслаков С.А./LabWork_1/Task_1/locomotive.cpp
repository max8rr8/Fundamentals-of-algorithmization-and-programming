#include "locomotive.h"
#include <QPainter>
#include "smoke.h"
Locomotive::Locomotive() : Moving_rect(){
};

/*void Locomotive::paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    painter->setBrush(Qt::red);
    int width = 400;
    int height = 200;
    int y = -100;
    painter->drawRect(x, y, width, height);
    painter->setBrush(Qt::blue);
    painter->drawRect(x + 50, y + 30, 80, 130);  // First window
    painter->drawRect(x + 250, y + 30, 80, 130); // Second window
    painter->setBrush(Qt::black);
    painter->drawEllipse(x + 20, y + 180, 50, 50);    // First wheel
    painter->drawEllipse(x + 120, y + 180, 50, 50);   // Second wheel
    painter->drawEllipse(x + 220, y + 180, 50, 50);   // Third wheel
    painter->drawEllipse(x + 320, y + 180, 50, 50);   // Fourth wheel
    painter->drawRect(x + width - 20,-160,20,60);
}
*/
void Locomotive::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(Qt::red);
    int width = 400;
    int height = 200;
    int y = -100;
    painter->drawRect(x, y, width, height);
    painter->setBrush(Qt::blue);
    painter->drawRect(x + 50, y + 30, 80, 130);  // First window
    painter->drawRect(x + 250, y + 30, 80, 130); // Second window
    painter->setBrush(Qt::black);
    painter->drawEllipse(x + 20, y + 180, 50, 50);    // First wheel
    painter->drawEllipse(x + 120, y + 180, 50, 50);   // Second wheel
    painter->drawEllipse(x + 220, y + 180, 50, 50);   // Third wheel
    painter->drawEllipse(x + 320, y + 180, 50, 50);   // Fourth wheel
    //painter->drawRect(x + width - 20, -160, 20, 60);

    drawTube(painter);
}

void Locomotive::drawTube(QPainter* painter)
{
    painter->setBrush(Qt::black);
    int tubeWidth = 20;
    int tubeHeight = 60;
    int tubeX = x + 380; // Adjust the position of the tube based on your needs
    int tubeY = -160;   // Adjust the position of the tube based on your needs
    tubeRect = QRectF(tubeX, tubeY, tubeWidth, tubeHeight);
    painter->drawRect(tubeRect);
}

void Locomotive::emitSmoke()
{
    Smoke* smoke = new Smoke();
    int smokeX = tubeRect.x() + tubeRect.width() / 2 - smoke->boundingRect().width() / 2;
    int smokeY = tubeRect.y() - smoke->boundingRect().height();
    smoke->setPos(smokeX, smokeY);
    scene()->addItem(smoke);
}
