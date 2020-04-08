#include "convolutionview.h"

#include <QPainter>

#include "presenters/convolutionpresentor.h"

ConvolutionView::ConvolutionView(ConvolutionInteractorListener *listener, QObject *parent) : MovingView(Convolution, parent)
{
    makePolygon();

    presentor = new ConvolutionPresentor();
    presentor->setView(this);

    if (listener != nullptr) {
        presentor->setInteractor(listener);
        setToolTip("Neuron_" + QString::number(presentor->getID()));
    }

    neuronColor = Qt::black;
    forwardColor = Qt::white;

    imageBounding = QRectF(-30, -30, 30, 30);
}

QPixmap ConvolutionView::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(neuronColor);
    painter.setBrush(forwardColor);
    painter.translate(50, 50);
    painter.drawRect(-30, -30, 60, 60);

    return pixmap;
}

QPolygonF ConvolutionView::getPolygon() {
    return polygon;
}

void ConvolutionView::setPosition(QPointF position) {
    presentor->setPosition(position.x(), position.y());
}

QRectF ConvolutionView::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void ConvolutionView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(neuronColor);
    painter->setBrush(forwardColor);
    painter->drawRect(-30, -30, 60, 60);

    if (isSelected()) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawRect(boundingRect());
    }

    painter->drawImage(imageBounding, image);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void ConvolutionView::setOutValue(QImage img) {
    image = img;
    updateItem(this);
}

void ConvolutionView::makePolygon() {
    QRectF rect = boundingRect();
    polygon << rect.topLeft() << rect.topRight() << rect.bottomRight() << rect.bottomLeft() << rect.topLeft();
}

void ConvolutionView::updatePosition(double x, double y) {
    this->setPos(x, y);
    updateArrowsPosition();
}

unsigned long ConvolutionView::getID() {
    return presentor->getID();
}

void ConvolutionView::setActive(bool enable) {
    neuronColor = enable ? Qt::green : Qt::black;
}

void ConvolutionView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
}

bool ConvolutionView::isOutputNeuron() {
    return false;
}

ConvolutionView::~ConvolutionView() {
    removeArrows();

    delete presentor;
    presentor = nullptr;
}
