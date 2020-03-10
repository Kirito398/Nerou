#include "dataview.h"

#include <QPainter>

#include "presenters/datapresentor.h"

DataView::DataView(DataInteractorListener *listener, QObject *parent) : MovingView(Data, parent)
{
    makePolygon();

    presentor = new DataPresentor();
    presentor->setView(this);

    if (listener != nullptr)
        presentor->setInteractor(listener);
}

void DataView::updatePosition(double x, double y) {
    this->setPos(x, y);
    updateArrowsPosition();
}

void DataView::setPosition(QPointF position) {
    presentor->setPosition(position.x(), position.y());
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
    painter.drawRect(-30, -30, 60, 60);

    return pixmap;
}

QPolygonF DataView::getPolygon() {
    return polygon;
}

QRectF DataView::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void DataView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawRect(-30, -30, 60, 60);

    if (isSelected()) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawRect(boundingRect());
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void DataView::makePolygon() {
    QRectF rect = boundingRect();
    polygon << rect.topLeft() << rect.topRight() << rect.bottomRight() << rect.bottomLeft() << rect.topLeft();
}

DataView::~DataView() {

}
