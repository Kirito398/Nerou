#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPolygonF>
#include <QVector>

#include <interfaces/moveiteminterface.h>
#include <interactors/maininteractor.h>
#include <interfaces/PaintSceneInterface.h>
#include <models/arrowitem.h>

class ArrowItem;

class MoveItem : public QObject, public QGraphicsItem, public MoveItemInterface
{
public:
    MoveItem(QPointF position, QObject *parent = 0);
    void setView(PaintSceneInterface *view);
    QPolygonF getPolygon() const;
    bool addArrow(ArrowItem* arrow);
    ModelItem* getItem();

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void setPosition(float posX, float posY) override;
    void makePolygon();
    bool isArrowAlreadyAdded(ArrowItem* arrow);

private:
    ModelItem *listener;
    PaintSceneInterface *view;
    QPolygonF polygon;
    QVector<ArrowItem *> inputArrows;
    QVector<ArrowItem *> outputArrows;
};

#endif // MOVEITEM_H
