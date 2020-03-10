#include "arrowview.h"

#include <QPainter>

#include "interfaces/movingviewinterface.h"
#include "presenters/arrowpresentor.h"

ArrowView::ArrowView(ArrowInteractorListener *interactor, MovingViewInterface *startView, MovingViewInterface *endView, QGraphicsItem *parent) : QGraphicsLineItem(parent)
{
    this->startView = startView;
    this->endView = endView;

    setFlag(QGraphicsItem::ItemIsSelectable);

    presentor = new ArrowPresentor();
    presentor->setView(this);
    presentor->setInteractor(interactor);
}

void ArrowView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (startView->getItem()->collidesWithItem(endView->getItem()))
        return;

    QPen mPen = pen();
    mPen.setColor(Qt::black);
    painter->setPen(mPen);
    painter->setBrush(Qt::black);

    qreal arrowSize = 10;

    QLineF centerLine(startView->getPosition(), endView->getPosition());
    QPolygonF endPolygon = endView->getPolygon();
    QPointF p1 = endPolygon.first() + endView->getPosition();
    QPointF p2, intersectPoint;
    QLineF polyLine;

    for (int i = 1; i < endPolygon.count(); ++i) {
        p2 = endPolygon.at(i) + endView->getPosition();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, startView->getPosition()));

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

QRectF ArrowView::boundingRect() const {
    return selectionPolygon().boundingRect();
}

QPainterPath ArrowView::shape() const {
    QPainterPath path;
    path.addPolygon(selectionPolygon());
    return path;
}

QPolygonF ArrowView::selectionPolygon() const {
    QPolygonF polygon;
    qreal size = 10;

    QLineF newLine = line();
    newLine.setLength(line().length() + 15);

    qreal lineCenterX = (line().p1().x() + line().p2().x()) / 2.0;
    qreal lineCenterY = (line().p1().y() + line().p2().y()) / 2.0;
    qreal newLineCenterX = (newLine.p1().x() + newLine.p2().x()) / 2.0;
    qreal newLineCenterY = (newLine.p1().y() + newLine.p2().y()) / 2.0;

    qreal deltaX = lineCenterX - newLineCenterX;
    qreal deltaY = lineCenterY - newLineCenterY;

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

void ArrowView::updatePosition() {
    QLineF line(mapFromItem(startView->getItem(), 0, 0), mapFromItem(endView->getItem(), 0, 0));
    setLine(line);
}

MovingViewInterface* ArrowView::getStartView() {
    return startView;
}

MovingViewInterface* ArrowView::getEndView() {
    return endView;
}

ArrowView::~ArrowView() {
//    MainInteractor::getInstance()->removeSinaps(item);
//    delete item;
}
