#include "dataview.h"

#include <QPainter>

#include <QThread>

#include "presenters/datapresentor.h"

DataView::DataView(DataInteractorListener *listener, QObject *parent) : MovingView(Data, parent)
{
    makePolygon();

    presentor = new DataPresentor();
    presentor->setView(this);

    if (listener != nullptr)
        presentor->setInteractor(listener);

    bounding = QRectF (-30, -30, 60, 60);
    imageBounding = QRectF(-30, -30, 30, 30);
}

void DataView::updatePosition(double x, double y) {
    this->setPos(x, y);
    updateArrowsPosition();
}

void DataView::setPosition(QPointF position) {
    presentor->setPosition(position.x(), position.y());
}

void DataView::setImage(QString path) {
    image = QImage(path);
    updateScene();
}

unsigned long DataView::getID() {
    return presentor->getID();
}

QPixmap DataView::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.translate(50, 50);
    painter.drawRect(bounding);

    return pixmap;
}

QPolygonF DataView::getPolygon() {
    return polygon;
}

QRectF DataView::boundingRect() const {
    return bounding;
}

void DataView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawRect(bounding);

    if (isSelected()) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawRect(bounding);
    }

    painter->drawImage(imageBounding, image);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void DataView::makePolygon() {
    polygon << bounding.topLeft() << bounding.topRight() << bounding.bottomRight() << bounding.bottomLeft() << bounding.topLeft();
}

DataView::~DataView() {
    removeArrows();

    delete presentor;
    presentor = nullptr;
}