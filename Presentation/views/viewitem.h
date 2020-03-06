#ifndef VIEWITEM_H
#define VIEWITEM_H

#include <QObject>
#include <QGraphicsItem>

#include <interfaces/PaintSceneInterface.h>

class ViewItem : public QObject, public QGraphicsItem
{
public:
    ViewItem(QPointF position, ModelItem::ItemType type = ModelItem::Perceptron,  QObject *parent = nullptr);
    ~ViewItem() override;
    void setView(PaintSceneInterface *view);
    bool addArrow(ArrowItem* arrow);
    ModelItem* getItem();
    void setPosition(QPointF position);
    void removeArrow(ArrowItem* arrow);
    void removeArrows();
    virtual QPixmap getItemIcon() const = 0;
    virtual QPolygonF getPolygon() const = 0;

private:
    virtual void makePolygon() = 0;
    virtual void setPosition(double posX, double posY);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void updateArrowsPosition();

protected:
    ModelItem *listener;
    PaintSceneInterface *view;
    QPolygonF polygon;

private:
    QVector<ArrowItem *> inputArrows;
    QVector<ArrowItem *> outputArrows;
    ModelItem::ItemType type;
};

#endif // VIEWITEM_H
