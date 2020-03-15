#ifndef MOVINGITEMINTERFACE_H
#define MOVINGITEMINTERFACE_H

class QPointF;
class QPolygonF;
class QGraphicsItem;
class ArrowInterface;

class MovingViewInterface
{
public:
    virtual QPointF getPosition() = 0;
    virtual QPolygonF getPolygon() = 0;
    virtual QGraphicsItem* getItem() = 0;
    virtual void removeArrow(ArrowInterface *arrow) = 0;
    virtual int getInputArrowNumber() = 0;
    virtual int getOutputArrowNumber() = 0;
};

#endif // MOVINGITEMINTERFACE_H
