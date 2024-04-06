#ifndef SHAPE_H
#define SHAPE_H
#include <QGraphicsObject>
#include <QPainter>
#include <QVector>
class Shape : public QGraphicsObject
{
    Q_OBJECT
protected:
    double radius = 50;
    double centerx;
    double centery;
    QVector<QPointF> points;
    QVector<double> pointsx;
    QVector<double> pointsy;
public:
    double rotatecenterx = 0;
    double rotatecentery = 0;
    double rotate_angle = 0;
    double X = 0;
    double Y = 0;
    double scale = 1;
    QPointF move = {X,Y};
    Shape() = default;
    bool center_connected = true;
    virtual void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
    void changescale(double spinscale);
    virtual void changerad(double spinrad);
    void rotate(double spinangle);
    virtual qreal area();
    virtual qreal perimeter();
    virtual void calculate_points();
    virtual void number_apexes(int number);
    virtual void centerset();
    void changerotatecenterx(double spincoord);
    void changerotatecentery(double spincoord);
    void move_x(double spinX);
    void move_y(double spinY);
};

#endif // SHAPE_H
