//#include "convolutionitem.h"

//ConvolutionItem::ConvolutionItem(QPointF position, QObject *parent) : MoveItem(position, ModelItem::Convolution, parent)
//{
//    makePolygon();
//}

//QPixmap ConvolutionItem::getItemIcon() const {
//    QPixmap pixmap(100, 100);
//    pixmap.fill(Qt::transparent);
//    QPainter painter(&pixmap);

//    painter.setPen(Qt::black);
//    painter.setBrush(Qt::green);
//    painter.translate(50, 50);
//    painter.drawRect(-30, -30, 60, 60);

//    return pixmap;
//}

//QPolygonF ConvolutionItem::getPolygon() const {
//    return polygon;
//}

//QRectF ConvolutionItem::boundingRect() const {
//    return QRectF (-30, -30, 60, 60);
//}

//void ConvolutionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    painter->setPen(Qt::black);
//    painter->setBrush(Qt::green);
//    painter->drawRect(-30, -30, 60, 60);

//    if (isSelected()) {
//        painter->setPen(Qt::blue);
//        painter->setBrush(QColor(0, 0, 255, 50));
//        painter->drawRect(boundingRect());
//    }

//    Q_UNUSED(option)
//    Q_UNUSED(widget)
//}

//void ConvolutionItem::makePolygon() {
//    QRectF rect = boundingRect();
//    polygon << rect.topLeft() << rect.topRight() << rect.bottomRight() << rect.bottomLeft() << rect.topLeft();
//}
