#ifndef CONVOLUTIONVIEW_H
#define CONVOLUTIONVIEW_H

#include "movingview.h"
#include "listeners/convolutionviewlistener.h"

class ConvolutionPresentor;
class ConvolutionInteractorListener;

class ConvolutionView : public MovingView, public ConvolutionViewListener
{
public:
    ConvolutionView(ConvolutionInteractorListener *listener = nullptr, QObject *parent = nullptr);
    ~ConvolutionView();
    QPixmap getItemIcon() const override;
    QPolygonF getPolygon() override;
    void setPosition(QPointF position) override;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon() override;
    void updatePosition(double x, double y) override;
    unsigned long getID() override;
    void setActive(bool enable) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ConvolutionPresentor *presentor;
    QColor neuronColor, forwardColor;
};

#endif // CONVOLUTIONVIEW_H
