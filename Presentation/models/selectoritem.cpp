#include "selectoritem.h"

#include <QPainter>

#include "interfaces/PaintSceneInterface.h"

SelectorItem::SelectorItem(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    startPoint = mapFromScene(position);
    endPoint = startPoint;
}

void SelectorItem::setView(PaintSceneInterface *view) {
    this->view = view;
}

QRectF SelectorItem::boundingRect() const {
    return QRectF(startPoint, endPoint);
}

void SelectorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(QColor(0, 0, 255, 100)));
    painter->drawRect(boundingRect());

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void SelectorItem::setEndPoint(QPointF point) {
    endPoint = mapFromScene(point);
    this->update();
    view->updateScene();
}
