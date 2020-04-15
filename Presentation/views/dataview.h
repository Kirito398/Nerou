#ifndef DATAVIEW_H
#define DATAVIEW_H

#include "views/movingview.h"
#include "listeners/dataviewlistener.h"

class DataPresentor;
class DataInteractorListener;
class DataSetsDialog;
class DataParametersDialog;

class DataView : public MovingView, public DataViewListener
{
public:
    DataView(DataInteractorListener *listener = nullptr, QObject *parent = nullptr);
    ~DataView() override;
    QPixmap getItemIcon() const override;
    QPolygonF getPolygon() override;
    void setPosition(QPointF position) override;
    QBoxLayout *getPropertiesLayout() override;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon() override;
    void updatePosition(double x, double y) override;
    unsigned long getID() override;
    void setImage(QString path) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QStringList getOutputsNeuronsList() override;
    bool isOutputNeuron() override;

private:
    DataPresentor *presentor;
    QImage image;
    QRectF bounding, imageBounding;
    DataSetsDialog *setsDialog;
    DataParametersDialog *parametersDialog;
    QColor brushColor;
    QBoxLayout *propertiesBox;

private slots:
    void onParametersUpdated();
};

#endif // DATAVIEW_H
