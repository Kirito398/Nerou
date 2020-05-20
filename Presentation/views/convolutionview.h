#ifndef CONVOLUTIONVIEW_H
#define CONVOLUTIONVIEW_H

#include "movingview.h"
#include "listeners/convolutionviewlistener.h"

class ConvolutionPresentor;
class ConvolutionInteractorListener;
class ConvolutionParametersDialog;

class ConvolutionView : public MovingView, public ConvolutionViewListener
{
public:
    ConvolutionView(ConvolutionInteractorListener *listener = nullptr, QObject *parent = nullptr);
    ~ConvolutionView();
    QPixmap getItemIcon() const override;
    QPolygonF getPolygon() override;
    void setPosition(QPointF position) override;
    void setActivateFunctionType(int type);
    QBoxLayout * getPropertiesLayout() override;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon() override;
    void updatePosition(double x, double y) override;
    unsigned long getID() override;
    void setActive(bool enable) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    bool isOutputNeuron() override;
    void setOutValue(QImage img) override;
    void onActivateFunctionTypeChanged(int type) override;
    int getActivateFunctionType() override;
    void onCoreSizeChanged(int size) override;
    int getCoreSize() override;
    void onPoolCoreSizeChanged(int size) override;
    int getPoolCoreSize() override;

private:
    ConvolutionPresentor *presentor;
    ConvolutionParametersDialog *parametersDialog;
    QColor neuronColor, forwardColor;
    QImage image;
    QRectF bounding, imageBounding;
};

#endif // CONVOLUTIONVIEW_H
