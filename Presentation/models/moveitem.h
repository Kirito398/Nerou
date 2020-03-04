#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPolygonF>
#include <QVector>
#include <QGraphicsScene>

#include <interfaces/moveiteminterface.h>
#include <interactors/maininteractor.h>
#include <interfaces/PaintSceneInterface.h>
#include <models/arrowitem.h>
#include <models/modelitem.h>

class ArrowItem;

class MoveItem : public QObject, public QGraphicsItem, public MoveItemInterface
{

public:
    MoveItem(QPointF position, ModelItem::ItemType type = ModelItem::Perceptron,  QObject *parent = nullptr);
    ~MoveItem() override;
    void setView(PaintSceneInterface *view);
    bool addArrow(ArrowItem* arrow);
    ModelItem* getItem();
    void setPosition(QPointF position);
    void removeArrow(ArrowItem* arrow);
    void removeArrows();
    virtual QPixmap getItemIcon() const = 0;
    virtual QPolygonF getPolygon() const = 0;

private:
    virtual void makePolygon() = 0;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void setPosition(double posX, double posY) override;
    bool isArrowAlreadyAdded(ArrowItem* arrow);
    void updateArrowsPosition();

protected:
    ModelItem *listener;
    PaintSceneInterface *view;
    QPolygonF polygon;

private:
    QVector<ArrowItem *> inputArrows;
    QVector<ArrowItem *> outputArrows;
    ModelItem::ItemType type;
};

#endif // MOVEITEM_H
