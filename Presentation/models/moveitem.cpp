#include "moveitem.h"

MoveItem::MoveItem(QPointF point, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(point);
}

QRectF MoveItem::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-30, -30, 60, 60);

    painter->drawText(mapFromScene(this->pos()) - QPointF(boundingRect().width() / 2.0f - 3.0f, 10.0f), this->objectName());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ArrowCursor));

    Q_UNUSED(event);
}
