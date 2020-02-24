#include "moveitem.h"

MoveItem::MoveItem(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    listener = MainInteractor::getInstance()->addNewItem(this);
    this->setPos(position);

    setFlag(QGraphicsItem::ItemIsSelectable);

    QRectF rect = boundingRect();
    polygon << rect.topLeft() << rect.topRight() << rect.bottomRight() << rect.bottomLeft() << rect.topLeft();
}

void MoveItem::setView(PaintSceneInterface *view) {
    this->view = view;
}

QPolygonF MoveItem::getPolygon() const {
    return polygon;
}

QRectF MoveItem::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-30, -30, 60, 60);

    if (isSelected()) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawRect(boundingRect());
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF position = mapToScene(event->pos());

    if (listener != nullptr)
        listener->setPosition(position.x(), position.y());
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ArrowCursor));

    QPointF position = mapToScene(event->pos());

    if (listener != nullptr)
        listener->setPosition(position.x(), position.y());
}

void MoveItem::setPosition(float posX, float posY) {
    this->setPos(QPointF(posX, posY));
}
