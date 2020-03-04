#ifndef DATAITEM_H
#define DATAITEM_H

#include <models/moveitem.h>

class DataItem : public MoveItem
{
public:
    DataItem(QPointF position, QObject *parent = nullptr);
    QPixmap getItemIcon() const override;
    QPolygonF getPolygon() const override;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon() override;
};

#endif // DATAITEM_H
