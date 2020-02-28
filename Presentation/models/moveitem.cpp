#include "moveitem.h"

MoveItem::MoveItem(QPointF position, ItemType type, QObject *parent) : QObject(parent), QGraphicsItem()
{
    listener = MainInteractor::getInstance()->addNewItem(this);
    this->setPos(position);

    setFlag(QGraphicsItem::ItemIsSelectable);

    makePolygon();
}

void MoveItem::setView(PaintSceneInterface *view) {
    this->view = view;
}

void MoveItem::makePolygon() {
    QRectF rect = boundingRect();
    polygon << rect.topLeft() << rect.topRight() << rect.bottomRight() << rect.bottomLeft() << rect.topLeft();
}

QPolygonF MoveItem::getPolygon() const {
    return polygon;
}

bool MoveItem::addArrow(ArrowItem* arrow) {
    if (isArrowAlreadyAdded(arrow))
        return false;

    MoveItem *startItem = arrow->getStartItem();
    MoveItem *endItem = arrow->getEndItem();

    if (startItem == this) {
        outputArrows.append(arrow);
        listener->addOutputItem(endItem->getItem());
    }

    if (endItem == this) {
        inputArrows.append(arrow);
        listener->addInputItem(startItem->getItem());
    }

    return true;
}

void MoveItem::removeArrow(ArrowItem* arrow) {
    if (outputArrows.contains(arrow)) {
        outputArrows.removeAll(arrow);
        listener->removeOutputItem(arrow->getEndItem()->getItem());
    }

    if (inputArrows.contains(arrow)) {
        inputArrows.removeAll(arrow);
        listener->removeInputItem(arrow->getStartItem()->getItem());
    }
}

void MoveItem::removeArrows() {
    for (auto arrow : inputArrows) {
        arrow->getStartItem()->removeArrow(arrow);
        arrow->getEndItem()->removeArrow(arrow);
        inputArrows.removeAll(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }

    for (auto arrow : outputArrows) {
        arrow->getStartItem()->removeArrow(arrow);
        arrow->getEndItem()->removeArrow(arrow);
        outputArrows.removeAll(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

bool MoveItem::isArrowAlreadyAdded(ArrowItem* arrow) {
    for (auto item : outputArrows)
        if (arrow->getStartItem() == item->getStartItem() && arrow->getEndItem() == item->getEndItem())
            return true;

    for (auto item : inputArrows)
        if (arrow->getStartItem() == item->getStartItem() && arrow->getEndItem() == item->getEndItem())
            return true;

    return false;
}

ModelItem* MoveItem::getItem() {
    return listener;
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
    QPointF deltaP = mapToScene(event->pos()) - this->pos();
    view->moveSelectedItem(deltaP);
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event)
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ArrowCursor));

    QPointF position = mapToScene(event->pos());

    if (listener != nullptr)
        listener->setPosition(position.x(), position.y());
}

void MoveItem::setPosition(double posX, double posY) {
    this->setPos(QPointF(posX, posY));
    updateArrowsPosition();
}

QPixmap MoveItem::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    painter.translate(50, 50);
    painter.drawRect(-30, -30, 60, 60);

    return pixmap;
}

void MoveItem::setPosition(QPointF position) {
    if (listener != nullptr)
        listener->setPosition(position.x(), position.y());
}

void MoveItem::updateArrowsPosition() {
    for(auto arrow : inputArrows)
        arrow->updatePosition();
}
