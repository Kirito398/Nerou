#include "arrowitem.h"

ArrowItem::ArrowItem(QPointF point, QObject *parent) : QObject(parent), QGraphicsItem()
{
    startPoint = mapFromScene(point);
    //endPoint = startPoint;
    endPoint = QPointF(startPoint.x() + 50, startPoint.y());

    endBoundingRect = QRectF(endPoint.x() - 5, endPoint.y() - 5, 10, 10);
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawLine(startPoint, endPoint);

    painter->setPen(Qt::blue);
    painter->setBrush(QColor(0, 0, 255, 50));
    painter->drawPolygon(selectionPolygon());

    painter->drawRect(endBoundingRect);
}

QRectF ArrowItem::boundingRect() const {
    return selectionPolygon().boundingRect();
}

QPainterPath ArrowItem::shape() const {
    QPainterPath path;
    path.addPolygon(selectionPolygon());
    return path;
}

void ArrowItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    endPoint = mapToScene(event->scenePos());
    endBoundingRect.moveTo(endPoint.x() - 5, endPoint.y() - 5);

    this->update();
    view->updateScene();
}

void ArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

}

void ArrowItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    this->update(boundingRect());
    view->updateScene();
}

void ArrowItem::setView(PaintSceneInterface *view) {
    this->view = view;
}

QPolygonF ArrowItem::selectionPolygon() const {
    QPolygonF polygon;
    QLineF line(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y());
    qreal size = 15;

    QLineF newLine = line;
    newLine.setLength(line.length() + 15);

    qreal deltaX = line.center().x() - newLine.center().x();
    qreal deltaY = line.center().y() - newLine.center().y();

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
