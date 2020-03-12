#ifndef ARROWVIEW_H
#define ARROWVIEW_H

#include <QGraphicsItem>

#include <math.h>

#include "interfaces/arrowinterface.h"
#include "listeners/arrowviewlistener.h"

class MovingViewInterface;
class ArrowPresentor;
class ArrowInteractorListener;
class PaintSceneInterface;

class ArrowView : public QGraphicsLineItem, public ArrowInterface, public ArrowViewListener
{
public:
    ArrowView(ArrowInteractorListener *interactor, MovingViewInterface *startView, MovingViewInterface *endView, QGraphicsItem *parent = nullptr);
    ~ArrowView() override;
    MovingViewInterface * getStartView() override;
    MovingViewInterface * getEndView() override;
    void updatePosition() override;
    void setView(PaintSceneInterface *interface);

private:
    QPolygonF selectionPolygon() const;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setActive(bool enable) override;

private:
    MovingViewInterface *startView;
    MovingViewInterface *endView;
    ArrowPresentor *presentor;
    PaintSceneInterface *view;
    QPolygonF arrowHead;
    QColor arrowColor;
};

#endif // ARROWVIEW_H
