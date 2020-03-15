#include "paintscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>

#include "views/dataview.h"
#include "views/arrowview.h"
#include "views/perceptronview.h"
#include "models/selectoritem.h"
#include "interactors/maininteractor.h"
#include "repositories/mainrepository.h"
#include "interfaces/mainwindowinterface.h"
#include "dialogs/addoutputneuronsdialog.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    interactor = MainInteractor::getInstance(new MainRepository());
    interactor->setView(this);
    line = nullptr;
    selector = nullptr;
    mode = PaintScene::Selector;
    viewType = MovingView::Perceptron;
}

void PaintScene::onNewPerceptronAdded(PerceptronInteractorListener *perceptron) {
    PerceptronView *view = new PerceptronView(perceptron);

    view->setView(this);
    view->setSelected(true);

    addItem(view);
}

void PaintScene::onNewDataAdded(DataInteractorListener *data) {
    DataView *view = new DataView(data);

    view->setView(this);
    view->setSelected(true);

    addItem(view);
}

void PaintScene::moveSelectedItem(QPointF delta) {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    for (auto item : selectedItems) {
        MovingView *view = dynamic_cast<MovingView *>(item);
        if (view != nullptr)
            view->setPosition(item->pos() + delta);
    }
}

void PaintScene::onViewsModePress(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item =  this->itemAt(event->scenePos(), QTransform());
    if (item == nullptr)
        addMovingView(event->scenePos());
    else
        item->setSelected(true);
}

void PaintScene::onArrowsModePress(QGraphicsSceneMouseEvent *event) {
    line = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
    addItem(line);
}

void PaintScene::onSelectorModePress(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item =  this->itemAt(event->scenePos(), QTransform());
    if (item == nullptr) {
        selector = new SelectorItem(event->scenePos());
        selector->setView(this);
        addItem(selector);
    } else {
        if (!item->isSelected()) {
            this->clearSelection();
            item->setSelected(true);
        }
    }
}

void PaintScene::onViewsModeMove(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);
}

void PaintScene::onArrowsModeMove(QGraphicsSceneMouseEvent *event) {
    if (line == nullptr)
        return;

    QLineF newLine(line->line().p1(), event->scenePos());
    line->setLine(newLine);
}

void PaintScene::onSelectorModeMove(QGraphicsSceneMouseEvent *event) {
    if (selector != nullptr)
        selector->setEndPoint(event->scenePos());

    QGraphicsScene::mouseMoveEvent(event);
}

void PaintScene::onViewsModeRelease(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}

void PaintScene::onArrowsModeRelease(QGraphicsSceneMouseEvent *event) {
    if (line == nullptr)
        return;

    addArrow();

    Q_UNUSED(event)
}

void PaintScene::onSelectorModeRelease(QGraphicsSceneMouseEvent *event) {
    if (selector == nullptr)
        return;

    QList<QGraphicsItem *> selectedItems = items(selector->boundingRect());

    for (auto item : selectedItems)
        item->setSelected(true);

    removeItem(selector);
    delete selector;

    Q_UNUSED(event)
}

void PaintScene::setMode(Mode mode) {
    this->mode = mode;
}

void PaintScene::setViewType(MovingView::ViewType type) {
    viewType = type;
}

MovingView::ViewType PaintScene::getViewType() {
    return viewType;
}

void PaintScene::addArrow() {
    QList<QGraphicsItem *> startItems = items(line->line().p1());
    if (startItems.count() && startItems.first() == line)
        startItems.removeFirst();

    QList<QGraphicsItem *> endItems = items(line->line().p2());
    if (endItems.count() && endItems.first() == line)
        endItems.removeFirst();

    if (startItems.count() && endItems.count() && startItems.first() != endItems.first()) {
        MovingView *startView = qgraphicsitem_cast<MovingView *>(startItems.first());
        MovingView *endView = qgraphicsitem_cast<MovingView *>(endItems.first());
        ArrowInteractorListener *listener = nullptr;

        if (startView->getType() == endView->getType()) {
            if (startView->getType() == MovingView::Perceptron)
                listener = interactor->createNewWeight(startView->getID(), endView->getID());

            if (startView->getType() == MovingView::Convolution)
                listener = interactor->createNewCore(startView->getID(), endView->getID());
        }

        if (startView->getType() != endView->getType()) {
            if (startView->getType() == MovingView::Data && endView->getType() == MovingView::Perceptron)
                listener = interactor->createNewWeight(startView->getID(), endView->getID());

            if (startView->getType() == MovingView::Data && endView->getType() == MovingView::Convolution)
                listener = interactor->createNewCore(startView->getID(), endView->getID());
        }

        if (listener != nullptr) {
            this->clearSelection();
            ArrowView *arrow = new ArrowView(listener, startView, endView);
            startView->addArrow(arrow);
            endView->addArrow(arrow);
            arrow->setSelected(true);
            arrow->setZValue(-1000.0);
            arrow->updatePosition();
            arrow->setView(this);
            addItem(arrow);
        }
    }

    removeItem(line);
    delete line;
    line = nullptr;
}

void PaintScene::addMovingView(QPointF position) {
    switch (viewType) {
    case MovingView::Perceptron : {
        interactor->createNewPerceptron(position.x(), position.y());
        break;
    }
    case MovingView::Convolution : {
        //interactor->
        break;
    }
    case MovingView::Data : {
        interactor->createNewData(position.x(), position.y());
        break;
    }
    }
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton)
        return;

    if (mode != Selector)
        this->clearSelection();

    switch (mode) {
    case Selector:
        onSelectorModePress(event);
        break;
    case Views:
        onViewsModePress(event);
        break;
    case Arrows:
        onArrowsModePress(event);
        break;
    }

    QGraphicsScene::mousePressEvent(event);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    switch (mode) {
    case Selector:
        onSelectorModeMove(event);
        break;
    case Arrows:
        onArrowsModeMove(event);
        break;
    case Views:
        onViewsModeMove(event);
        break;
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    switch (mode) {
    case Selector:
        onSelectorModeRelease(event);
        break;
    case Arrows:
        onArrowsModeRelease(event);
        break;
    case Views:
        onViewsModeRelease(event);
        break;
    }

    selector = nullptr;
    line = nullptr;
}

QPixmap PaintScene::getPerceptronIcon() const {
    return PerceptronView().getItemIcon();
}

QPixmap PaintScene::getDataIcon() const {
    return DataView().getItemIcon();
}

void PaintScene::onDeleteBtnClicked() {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    for (auto item : selectedItems) {
        ArrowView * arrowView = dynamic_cast<ArrowView *>(item);
        if (arrowView == nullptr)
            continue;
        delete item;
    }

    selectedItems = this->selectedItems();
    for (auto item : selectedItems) {
        MovingView *moveItem = dynamic_cast<MovingView *>(item);
        if (moveItem == nullptr)
            continue;
        delete item;
    }
}

void PaintScene::onAddOutputNeuronsActionClicked() {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    MovingView *inputView = nullptr;
    for (auto item : selectedItems) {
        inputView = dynamic_cast<MovingView *>(item);
        if (inputView != nullptr)
            break;
    }

    if (inputView == nullptr)
        return;

    AddOutputNeuronsDialog dlg;
    int result = dlg.exec();

    if (result == QDialog::Rejected)
        return;

    int number = dlg.getNeuronsNumber().toInt();

    if (number <= 0)
        return;

    clearSelectedItem();

    double delta = 120;
    double posX = inputView->pos().x() + 600;
    double posY = inputView->pos().y() - number / 2 * delta;

    for (int i = 0; i < number; i++)
        interactor->createNewPerceptron(posX, posY + delta * i);

    selectedItems.clear();
    selectedItems = this->selectedItems();

    for (auto item : selectedItems) {
        line = new QGraphicsLineItem(QLineF(inputView->pos(), item->pos()));
        addItem(line);
        addArrow();
    }
}

void PaintScene::onRunBtnClicked() {
    interactor->run();
}

void PaintScene::onStopActionClicked() {
    interactor->stop();
}

void PaintScene::onPauseActionClicked() {
    interactor->pause();
}

void PaintScene::onDebugActionClicked() {
    interactor->debugRun();
}

void PaintScene::setView(MainWindowInterface *interface) {
    view = interface;
}

QAction *PaintScene::getAction(int type) {
    return view->getAction(type);
}

void PaintScene::clearSelectedItem() {
    clearSelection();
}

void PaintScene::updateScene() {
    this->update();
}

void PaintScene::updateItem(QGraphicsItem *item) {
    QSizeF size = item->boundingRect().size();
    update(QRectF(item->pos() - QPointF(-size.width() / 2.0, -size.height() / 2.0), size));
    QCoreApplication::processEvents(QEventLoop::AllEvents);
}

void PaintScene::deleteItem(QGraphicsItem *item) {
    removeItem(item);
}
