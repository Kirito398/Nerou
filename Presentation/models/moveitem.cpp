#include "moveitem.h"

MoveItem::MoveItem(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    listener = MainInteractor::getInstance()->addNewItem(this);
    this->setPos(position);

    isSelected = false;
    isIOClicked = false;

    inCircle = QRectF(-30, -5, 10, 10);
    outCircle = QRectF(20, -5, 10, 10);
}

void MoveItem::setView(PaintSceneInterface *view) {
    this->view = view;
}

QRectF MoveItem::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-30, -30, 60, 60);

    if (isSelected) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawRect(boundingRect());
    }

    painter->setBrush(Qt::white);
    painter->drawEllipse(inCircle);
    painter->drawEllipse(outCircle);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF position = mapToScene(event->pos());

    if (listener != nullptr && !isIOClicked)
        listener->setPosition(position.x(), position.y());
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    if (outCircle.contains(event->pos())) {
        isIOClicked = true;
        view->onOutputCircleClicked(event->pos());
    } else
        isIOClicked = false;
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ArrowCursor));

    QPointF position = mapToScene(event->pos());

    if (listener != nullptr && !isIOClicked)
        listener->setPosition(position.x(), position.y());
}

void MoveItem::setPosition(float posX, float posY) {
    this->setPos(QPointF(posX, posY));
}
