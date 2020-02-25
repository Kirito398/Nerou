#include "arrowitem.h"

ArrowItem::ArrowItem(MoveItem* startItem, MoveItem* endItem, QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    this->startItem = startItem;
    this->endItem = endItem;

    setFlag(QGraphicsItem::ItemIsSelectable);
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (startItem->collidesWithItem(endItem))
        return;

    QPen mPen = pen();
    mPen.setColor(Qt::black);
    painter->setPen(mPen);
    painter->setBrush(Qt::black);

    qreal arrowSize = 10;

    QLineF centerLine(startItem->pos(), endItem->pos());
    QPolygonF endPolygon = endItem->getPolygon();
    QPointF p1 = endPolygon.first() + endItem->pos();
    QPointF p2, intersectPoint;
    QLineF polyLine;

    for (int i = 1; i < endPolygon.count(); ++i) {
        p2 = endPolygon.at(i) + endItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, startItem->pos()));

    double angle = atan2(-line().dy(), line().dx());
    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(arrowHead);

    if (isSelected()) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawPolygon(selectionPolygon());
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF ArrowItem::boundingRect() const {
    return selectionPolygon().boundingRect();
}

QPainterPath ArrowItem::shape() const {
    QPainterPath path;
    path.addPolygon(selectionPolygon());
    return path;
}

QPolygonF ArrowItem::selectionPolygon() const {
    QPolygonF polygon;
    qreal size = 10;

    QLineF newLine = line();
    newLine.setLength(line().length() + 15);

    qreal deltaX = line().center().x() - newLine.center().x();
    qreal deltaY = line().center().y() - newLine.center().y();

    qreal radAngle = newLine.angle() * M_PI / 180;
    qreal dx = size / 2 * sin(radAngle);
    qreal dy = size / 2 * cos(radAngle);
    QPointF offset1 = QPointF(dx + deltaX / 2, dy + deltaY / 2);
    QPointF offset2 = QPointF(-dx + deltaX / 2, -dy + deltaY / 2);

    polygon << newLine.p1() + offset1
            << newLine.p1() + offset2
            << newLine.p2() + offset2
            << newLine.p2() + offset1;

    return polygon;
}

void ArrowItem::setView(PaintSceneInterface *view) {
    this->view = view;
}

void ArrowItem::updatePosition() {
    QLineF line(mapFromItem(startItem, 0, 0), mapFromItem(endItem, 0, 0));
    setLine(line);
}

MoveItem* ArrowItem::getStartItem() {
    return startItem;
}

MoveItem* ArrowItem::getEndItem() {
    return endItem;
}
