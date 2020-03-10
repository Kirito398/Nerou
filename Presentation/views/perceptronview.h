#ifndef PERCEPTRONVIEW_H
#define PERCEPTRONVIEW_H

#include "movingview.h"
#include "listeners/perceptronviewlistener.h"

class PerceptronPresentor;
class PerceptronInteractorListener;

class PerceptronView : public MovingView, public PerceptronViewListener
{
public:
    PerceptronView(PerceptronInteractorListener *listener, QObject *parent = nullptr);
    QPixmap getItemIcon() const override;
    QPolygonF getPolygon() override;
    void setPosition(QPointF position) override;

private:
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon() override;
    void updatePosition(double x, double y) override;
    unsigned long getID() override;

private:
    PerceptronPresentor *presentor;
};

#endif // PERCEPTRONVIEW_H
