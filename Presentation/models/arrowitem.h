#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPolygonF>

#include <interfaces/PaintSceneInterface.h>
#include <models/moveitem.h>
//#include <models/sinapsmodel.h>

#include <math.h>

class MoveItem;

class ArrowItem : public QGraphicsLineItem
{
public:
    ArrowItem(MoveItem *startItem, MoveItem *endItem, QGraphicsItem *parent = nullptr);
    ~ArrowItem() override;
    void setView(PaintSceneInterface *view);
    void updatePosition();
    MoveItem* getStartItem();
    MoveItem* getEndItem();
    //void setItem(SinapsModel *item);
    //SinapsModel *getItem();

protected:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QPolygonF selectionPolygon() const;

private:
    PaintSceneInterface *view;
    MoveItem *startItem;
    MoveItem *endItem;
    //SinapsModel *item;
    QPolygonF arrowHead;
};

#endif // ARROWITEM_H
