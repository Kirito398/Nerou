#ifndef TABLEDATAVIEW_H
#define TABLEDATAVIEW_H

#include "views/movingview.h"
#include "listeners/tabledataviewlistener.h"

class TableDataInteractorListener;
class TableDataPresentor;
class TableDataParametersDialog;

class TableDataView : public MovingView, public TableDataViewListener
{
public:
    TableDataView(TableDataInteractorListener *listener = nullptr, QObject *parent = nullptr);
    ~TableDataView() override;
    void setLossFunctionType(int type);
    void setActivateFunctionType(int type);
    QPolygonF getPolygon() override;

private:
    QRectF boundingRect() const override;
    unsigned long getID() override;
    void setPosition(QPointF position) override;
    QPixmap getItemIcon() const override;
    bool isOutputNeuron() override;
    QBoxLayout *getPropertiesLayout() override;
    void makePolygon() override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void updatePosition(double x, double y) override;
    int getActivateFunctionType() override;
    void onActivateFunctionTypeChanged(int type) override;
    int getLossFunctionType() override;
    void onLossFunctionTypeChanged(int type) override;
    void openSetsDialog() override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


private:
    TableDataPresentor *presentor;
    QImage image;
    QRectF bounding, imageBounding;
    QColor brushColor;
    QBoxLayout *propertiesBox;
    TableDataParametersDialog *parametersDialog;
};

#endif // TABLEDATAVIEW_H
