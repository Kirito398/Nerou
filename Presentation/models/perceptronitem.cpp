#include "perceptronitem.h"

PerceptronItem::PerceptronItem(QPointF position, QObject *parent) : MoveItem(position, Perceptron, parent)
{
    makePolygon();
}

QRectF PerceptronItem::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void PerceptronItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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

void PerceptronItem::makePolygon() {
    QRectF rect = boundingRect();
    polygon << rect.topLeft() << rect.topRight() << rect.bottomRight() << rect.bottomLeft() << rect.topLeft();
}

QPixmap PerceptronItem::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    painter.translate(50, 50);
    painter.drawRect(-30, -30, 60, 60);

    return pixmap;
}

QPolygonF PerceptronItem::getPolygon() const {
    return polygon;
}
