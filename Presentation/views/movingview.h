#ifndef MOVINGVIEW_H
#define MOVINGVIEW_H

#include <QObject>
#include <QGraphicsItem>

#include "interfaces/movingviewinterface.h"

class PaintSceneInterface;
class ArrowInterface;

class MovingView : public QObject, public QGraphicsItem, public MovingViewInterface
{
public:
    MovingView(QPointF position, QObject *parent = nullptr);
    ~MovingView() override;
    void setView(PaintSceneInterface *view);
    bool addArrow(ArrowInterface* arrow);
    void setPosition(QPointF position);
    void removeArrow(ArrowInterface* arrow);
    void removeArrows();
    virtual QPixmap getItemIcon() const = 0;
    virtual QPolygonF getPolygon() const = 0;

private:
    virtual void makePolygon() = 0;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    bool isArrowAlreadyAdded(ArrowInterface* arrow);
    void updateArrowsPosition();

protected:
    PaintSceneInterface *view;
    QPolygonF polygon;

private:
    QVector<ArrowInterface *> inputArrows;
    QVector<ArrowInterface *> outputArrows;
};

#endif // MOVINGVIEW_H
