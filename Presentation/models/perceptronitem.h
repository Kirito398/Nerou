#ifndef PERCEPTRONITEM_H
#define PERCEPTRONITEM_H

#include <models/moveitem.h>


class PerceptronItem : public MoveItem
{
public:
    PerceptronItem(QPointF position, QObject *parent = nullptr);
    QPixmap getItemIcon() const override;
    QPolygonF getPolygon() const override;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon() override;
};

#endif // PERCEPTRONITEM_H
