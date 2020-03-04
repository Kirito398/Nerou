#include "dataitem.h"

DataItem::DataItem(QPointF position, QObject *parent) : MoveItem(position, ModelItem::Data, parent)
{
    makePolygon();
}

QPixmap DataItem::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.translate(50, 50);
    painter.drawRect(-30, -30, 60, 60);

    return pixmap;
}

QPolygonF DataItem::getPolygon() const {
    return polygon;
}

QRectF DataItem::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void DataItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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

void DataItem::makePolygon() {
    QRectF rect = boundingRect();
    polygon << rect.topLeft() << rect.topRight() << rect.bottomRight() << rect.bottomLeft() << rect.topLeft();
}
