#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <interfaces/PaintSceneInterface.h>

#include <math.h>

class ArrowItem : public QObject, public QGraphicsItem
{
public:
    ArrowItem(QPointF point, QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setView(PaintSceneInterface *view);
    QPainterPath shape() const override;

private:
    QPolygonF selectionPolygon() const;

private:
    QPointF startPoint, endPoint;
    PaintSceneInterface *view;
    QRectF endBoundingRect;
};

#endif // ARROWITEM_H
