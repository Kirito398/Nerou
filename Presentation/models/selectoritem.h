#ifndef SELECTORITEM_H
#define SELECTORITEM_H

#include <QObject>
#include <QGraphicsItem>

class PaintSceneInterface;

class SelectorItem : public QObject, public QGraphicsItem
{
public:
    SelectorItem(QPointF position, QObject *parent = nullptr);
    void setView(PaintSceneInterface *view);
    void setEndPoint(QPointF point);
    QRectF boundingRect() const override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
    QPointF startPoint, endPoint;
    PaintSceneInterface *view;
};

#endif // SELECTORITEM_H
