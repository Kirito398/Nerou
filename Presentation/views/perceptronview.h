#ifndef PERCEPTRONVIEW_H
#define PERCEPTRONVIEW_H

#include "movingview.h"
#include "listeners/perceptronviewlistener.h"

class PerceptronPresentor;
class PerceptronInteractorListener;

class PerceptronView : public MovingView, public PerceptronViewListener
{
public:
    PerceptronView(PerceptronInteractorListener *listener = nullptr, QObject *parent = nullptr);
    ~PerceptronView();
    QPixmap getItemIcon() const override;
    QPolygonF getPolygon() override;
    void setPosition(QPointF position) override;
    void setOutputNeuron(bool enable);

private:
    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon() override;
    void updatePosition(double x, double y) override;
    unsigned long getID() override;
    void setActive(bool enable) override;
    void setOutValue(QString value) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    PerceptronPresentor *presentor;
    QColor neuronColor;
    QString value;
};

#endif // PERCEPTRONVIEW_H
