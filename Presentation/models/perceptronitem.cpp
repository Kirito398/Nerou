#include "perceptronitem.h"

PerceptronItem::PerceptronItem(QPointF position, QObject *parent) : MoveItem(position, ModelItem::Perceptron, parent)
{
    makePolygon();
}

QRectF PerceptronItem::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void PerceptronItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawEllipse(-30, -30, 60, 60);

    if (isSelected()) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawPolygon(polygon);
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QPainterPath PerceptronItem::shape() const {
    QPainterPath path;
    path.addPolygon(polygon);
    return path;
}

void PerceptronItem::makePolygon() {
    for (int i = -30; i <= 30; i++)
        polygon << QPointF(i, sqrt(900 - pow(i, 2.0)));

    for (int i = 30; i >= -30; i--)
        polygon << QPointF(i, -sqrt(900 - pow(i, 2.0)));
}

QPixmap PerceptronItem::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    painter.translate(50, 50);
    painter.drawEllipse(-30, -30, 60, 60);

    return pixmap;
}

QPolygonF PerceptronItem::getPolygon() const {
    return polygon;
}
