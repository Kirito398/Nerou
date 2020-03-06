#ifndef DATAVIEW_H
#define DATAVIEW_H

class DataView
{
public:
    DataView();
    QPixmap getItemIcon() const;
    QPolygonF getPolygon() const;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void makePolygon();
    void initData();

private:
    unsigned int rowCount;
    unsigned int columnCount;
    double **data;
};

#endif // DATAVIEW_H
