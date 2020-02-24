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

    qreal arrowSize = 20;

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
}

QRectF ArrowItem::boundingRect() const {
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath ArrowItem::shape() const {
    QPainterPath path;
    path.addPolygon(arrowHead);
    return path;
}

void ArrowItem::setView(PaintSceneInterface *view) {
    this->view = view;
}

void ArrowItem::updatePosition() {
    QLineF line(mapFromItem(startItem, 0, 0), mapFromItem(endItem, 0, 0));
    setLine(line);
}
