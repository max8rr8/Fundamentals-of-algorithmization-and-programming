#ifndef PAINTSCENE_H
#define PAINTSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
class paintscene : public QGraphicsScene
{
    Q_OBJECT
public:
    paintscene(QObject* parent = nullptr);
signals:
    void mousePressed(const QPointF &position);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    bool holdmouse;
    QPointF lastMousePos;
};

#endif // PAINTSCENE_H
