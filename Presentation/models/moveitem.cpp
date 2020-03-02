#include "moveitem.h"

MoveItem::MoveItem(QPointF position, ModelItem::ItemType type, QObject *parent) : QObject(parent), QGraphicsItem()
{
    listener = MainInteractor::getInstance()->addNewItem(this, type);
    this->setPos(position);
    this->type = type;

    setFlag(QGraphicsItem::ItemIsSelectable);
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

void MoveItem::setView(PaintSceneInterface *view) {
    this->view = view;
}

bool MoveItem::addArrow(ArrowItem* arrow) {
    if (isArrowAlreadyAdded(arrow))
        return false;

    MoveItem *startItem = arrow->getStartItem();
    MoveItem *endItem = arrow->getEndItem();

    if (startItem == this)
        outputArrows.append(arrow);

    if (endItem == this)
        inputArrows.append(arrow);

    return true;
}

void MoveItem::removeArrow(ArrowItem* arrow) {
    if (outputArrows.contains(arrow)) {
        outputArrows.removeAll(arrow);
        listener->removeOutputSinaps(arrow->getItem());
    }

    if (inputArrows.contains(arrow)) {
        inputArrows.removeAll(arrow);
        listener->removeInputSinaps(arrow->getItem());
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

void MoveItem::setPosition(double posX, double posY) {
    this->setPos(QPointF(posX, posY));
    updateArrowsPosition();
}

void MoveItem::setPosition(QPointF position) {
    if (listener != nullptr)
        listener->setPosition(position.x(), position.y());
}

void MoveItem::updateArrowsPosition() {
    for(auto arrow : inputArrows)
        arrow->updatePosition();
}

MoveItem::~MoveItem() {
    MainInteractor::getInstance()->removeItem(this);
}
