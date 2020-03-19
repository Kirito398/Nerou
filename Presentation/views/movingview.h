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
    enum ViewType {Data, Perceptron, Convolution};
    MovingView(ViewType type, QObject *parent = nullptr);
    ~MovingView() override;
    void setView(PaintSceneInterface *view);
    bool addArrow(ArrowInterface* arrow);
    void removeArrow(ArrowInterface* arrow) override;
    void removeArrows();
    ViewType getType();
    virtual unsigned long getID() = 0;
    virtual void setPosition(QPointF position) = 0;
    virtual QPixmap getItemIcon() const = 0;

private:
    virtual void makePolygon() = 0;
    QPointF getPosition() override;
    QGraphicsItem * getItem() override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override = 0;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    int getInputArrowNumber() override;
    int getOutputArrowNumber() override;
    bool isArrowAlreadyAdded(ArrowInterface* arrow);

protected:
    virtual void initMenu();
    virtual bool isOutputNeuron() = 0;
    void updateArrowsPosition();
    void updateScene();
    void updateItem(QGraphicsItem *item);
    QStringList outputsNeuronsList();

protected:
    PaintSceneInterface *view;
    QPolygonF polygon;
    QMenu *menu;

private:
    QVector<ArrowInterface *> inputArrows;
    QVector<ArrowInterface *> outputArrows;
    ViewType type;
};

#endif // MOVINGVIEW_H
