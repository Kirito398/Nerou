#ifndef CONVOLUTIONITEM_H
#define CONVOLUTIONITEM_H

#include <models/moveitem.h>

class ConvolutionItem : public MoveItem
{
public:
    ConvolutionItem(QPointF position, QObject *parent = nullptr);
    QPixmap getItemIcon() const override;
    QPolygonF getPolygon() const override;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon() override;
};

#endif // CONVOLUTIONITEM_H
