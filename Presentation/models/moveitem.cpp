#include "moveitem.h"

MoveItem::MoveItem(QObject *parent) : QObject(parent), QGraphicsItem()
{
    interactor = MainInteractor::getInstance();
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
    QPointF position = mapToScene(event->pos());
    interactor->setItemPosition(position.x(), position.y());
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    interactor->setCurrentItem(this->objectName().toStdString());

    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ArrowCursor));

    QPointF position = mapToScene(event->pos());
    interactor->setItemPosition(position.x(), position.y());

    Q_UNUSED(event);
}

void MoveItem::setPosition(float posX, float posY) {
    this->setPos(QPointF(posX, posY));
}

void MoveItem::setPosition(QPointF position) {
    interactor->setCurrentItem(this->objectName().toStdString());
    interactor->setItemPosition(position.x(), position.y());
}
