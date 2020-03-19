#include "perceptronview.h"

#include <QPainter>
#include <math.h>

#include "presenters/perceptronpresentor.h"

PerceptronView::PerceptronView(PerceptronInteractorListener *listener, QObject *parent) : MovingView(Perceptron, parent)
{
    makePolygon();

    presentor = new PerceptronPresentor();
    presentor->setView(this);

    if (listener != nullptr) {
        presentor->setInteractor(listener);
        setToolTip("Neuron_" + QString::number(presentor->getID()));
    }

    neuronColor = Qt::black;
    forwardNeuronBrush = QColor(255, 223, 143);
    outputNeuronBrush = QColor(255, 92, 106);
    value = "";
}

QPixmap PerceptronView::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(neuronColor);
    painter.setBrush(forwardNeuronBrush);
    painter.translate(50, 50);
    painter.drawEllipse(-30, -30, 60, 60);

    return pixmap;
}

QPolygonF PerceptronView::getPolygon() {
    return polygon;
}

QPainterPath PerceptronView::shape() const {
    QPainterPath path;
    path.addPolygon(polygon);
    return path;
}

void PerceptronView::setPosition(QPointF position) {
    presentor->setPosition(position.x(), position.y());
}

QRectF PerceptronView::boundingRect() const {
    return QRectF (-30, -30, 60, 60);
}

void PerceptronView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(neuronColor);

    if (presentor->isOutputNeuron())
        painter->setBrush(outputNeuronBrush);
    else
        painter->setBrush(forwardNeuronBrush);

    painter->drawEllipse(-30, -30, 60, 60);

    if (isSelected()) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawPolygon(polygon);
    }

    painter->setPen(neuronColor);
    painter->drawText(QPointF(-25, 5), value);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void PerceptronView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
}

void PerceptronView::setOutputNeuron(bool enable) {
    if (isOutputNeuron() == enable)
        return;

    presentor->setOutputNeuron(enable);
    removeOutputArrows();
    initMenu();
}

void PerceptronView::makePolygon() {
    for (int i = -30; i <= 30; i++)
        polygon << QPointF(i, sqrt(900 - pow(i, 2.0)));

    for (int i = 30; i >= -30; i--)
        polygon << QPointF(i, -sqrt(900 - pow(i, 2.0)));
}

void PerceptronView::updatePosition(double x, double y) {
    this->setPos(x, y);
    updateArrowsPosition();
}

bool PerceptronView::isOutputNeuron() {
    return presentor->isOutputNeuron();
}

void PerceptronView::setActive(bool enable) {
    neuronColor = enable ? Qt::green : Qt::black;
}

void PerceptronView::setOutValue(QString value) {
    this->value = value;
    updateItem(this);
}

unsigned long PerceptronView::getID() {
    return presentor->getID();
};

PerceptronView::~PerceptronView() {
    removeArrows();

    delete presentor;
    presentor = nullptr;
}
