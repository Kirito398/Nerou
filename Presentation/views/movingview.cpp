#include "movingview.h"

#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QVector>

#include "interfaces/arrowinterface.h"
#include "interfaces/PaintSceneInterface.h"

MovingView::MovingView(ViewType type, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->type = type;
    setFlag(QGraphicsItem::ItemIsSelectable);
    view = nullptr;
}

MovingView::ViewType MovingView::getType() {
    return type;
}

QPointF MovingView::getPosition() {
    return this->pos();
}

QGraphicsItem *MovingView::getItem() {
    return this;
}

void MovingView::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF deltaP = mapToScene(event->pos()) - this->pos();
    view->moveSelectedItem(deltaP);
}

void MovingView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event)
}

void MovingView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->setCursor(QCursor(Qt::ArrowCursor));

    setPosition(mapToScene(event->pos()));
}

void MovingView::setView(PaintSceneInterface *view) {
    this->view = view;
}

bool MovingView::addArrow(ArrowInterface* arrow) {
    if (isArrowAlreadyAdded(arrow))
        return false;

    MovingViewInterface *startItem = arrow->getStartView();
    MovingViewInterface *endItem = arrow->getEndView();

    if (startItem == this)
        outputArrows.append(arrow);

    if (endItem == this)
        inputArrows.append(arrow);

    return true;
}

void MovingView::removeArrow(ArrowInterface* arrow) {
    if (outputArrows.contains(arrow)) {
        QMutableVectorIterator<ArrowInterface *> it(outputArrows);

        while(it.hasNext()) {
            if (it.next() == arrow)
                it.remove();
        }
    }

    if (inputArrows.contains(arrow)) {
        QMutableVectorIterator<ArrowInterface *> it(inputArrows);

        while(it.hasNext()) {
            if (it.next() == arrow)
                it.remove();
        }
    }
}

void MovingView::removeArrows() {
    QMutableVectorIterator<ArrowInterface *> input(inputArrows);

    while (input.hasNext()) {
        ArrowInterface *arrow = input.next();
        input.remove();
        delete arrow;
    }

    QMutableVectorIterator<ArrowInterface *> output(inputArrows);

    while(output.hasNext()) {
        ArrowInterface *arrow = output.next();
        output.remove();
        delete arrow;
    }
}

bool MovingView::isArrowAlreadyAdded(ArrowInterface* arrow) {
    for (auto item : outputArrows)
        if (arrow->getStartView() == item->getStartView() && arrow->getEndView() == item->getEndView())
            return true;

    for (auto item : inputArrows)
        if (arrow->getStartView() == item->getStartView() && arrow->getEndView() == item->getEndView())
            return true;

    return false;
}

void MovingView::updateArrowsPosition() {
    for(auto arrow : inputArrows)
        arrow->updatePosition();
}

MovingView::~MovingView() {
    if (view != nullptr)
        view->deleteItem(this);
}
