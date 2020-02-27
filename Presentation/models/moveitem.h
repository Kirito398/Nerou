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
    MoveItem(QPointF position, QObject *parent = nullptr);
    void setView(PaintSceneInterface *view);
    QPolygonF getPolygon() const;
    bool addArrow(ArrowItem* arrow);
    ModelItem* getItem();
    void setPosition(QPointF position);

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setPosition(double posX, double posY) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void makePolygon();
    bool isArrowAlreadyAdded(ArrowItem* arrow);
    void updateArrowsPosition();

private:
    ModelItem *listener;
    PaintSceneInterface *view;
    QPolygonF polygon;
    QVector<ArrowItem *> inputArrows;
    QVector<ArrowItem *> outputArrows;
};

#endif // MOVEITEM_H
