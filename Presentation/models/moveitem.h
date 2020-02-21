#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <interfaces/moveiteminterface.h>
#include <interactors/maininteractor.h>
#include <interfaces/PaintSceneInterface.h>

class MoveItem : public QObject, public QGraphicsItem, public MoveItemInterface
{
public:
    MoveItem(QPointF position, QObject *parent = 0);
    void setView(PaintSceneInterface *view);

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void setPosition(float posX, float posY) override;

private:
    ModelItem *listener;
    PaintSceneInterface *view;
    bool isSelected, isIOClicked;
    QRectF inCircle, outCircle;
};

#endif // MOVEITEM_H
