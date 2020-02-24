#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include <interfaces/PaintSceneInterface.h>
#include <models/moveitem.h>

#include <math.h>

class ArrowItem : public QGraphicsLineItem
{
public:
    ArrowItem(MoveItem *startItem, MoveItem *endItem, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setView(PaintSceneInterface *view);
    void updatePosition();

private:


private:
    PaintSceneInterface *view;
    MoveItem *startItem;
    MoveItem *endItem;
    QPolygonF arrowHead;
};

#endif // ARROWITEM_H
