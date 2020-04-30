#include "tabledataview.h"

#include <QPainter>

#include "presenters/tabledatapresentor.h"
#include "dialogs/tabledataparametersdialog.h"

TableDataView::TableDataView(TableDataInteractorListener *listener, QObject *parent) : MovingView(TableData ,parent)
{
    makePolygon();

    propertiesBox = nullptr;

    presentor = new TableDataPresentor();
    presentor->setView(this);

    if (listener != nullptr) {
        presentor->setInteractor(listener);
        setToolTip("Neuron_" + QString::number(presentor->getID()));
    }

    bounding = QRectF (-30, -30, 60, 60);
    imageBounding = QRectF(-30, -30, 30, 30);

    brushColor = QColor(115, 255, 100);

    parametersDialog = nullptr;
}

unsigned long TableDataView::getID() {
    return presentor->getID();
};

void TableDataView::setPosition(QPointF position) {
    presentor->setPosition(position.x(), position.y());
}

QPixmap TableDataView::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(Qt::black);
    painter.setBrush(brushColor);
    painter.translate(50, 50);
    painter.drawRect(bounding);

    return pixmap;
}

QPolygonF TableDataView::getPolygon() {
    return polygon;
}

QRectF TableDataView::boundingRect() const {
    return bounding;
}

bool TableDataView::isOutputNeuron() {
    return false;
}

QBoxLayout *TableDataView::getPropertiesLayout() {
    if (parametersDialog == nullptr)
        parametersDialog = new TableDataParametersDialog(this);

    return parametersDialog->getMainLayout();
}

void TableDataView::makePolygon() {
    polygon << bounding.topLeft() << bounding.topRight() << bounding.bottomRight() << bounding.bottomLeft() << bounding.topLeft();
}

void TableDataView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    painter->setBrush(brushColor);
    painter->drawRect(bounding);

    if (isSelected()) {
        painter->setPen(Qt::blue);
        painter->setBrush(QColor(0, 0, 255, 50));
        painter->drawRect(bounding);
    }

    painter->drawImage(imageBounding, image);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void TableDataView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event)

    openSetsDialog();
}

void TableDataView::updatePosition(double x, double y) {
    this->setPos(x, y);
    updateArrowsPosition();
}

int TableDataView::getActivateFunctionType() {
    return presentor->getActivateFunctionType();
}

void TableDataView::onActivateFunctionTypeChanged(int type) {
    QList<QGraphicsItem *> selectedItems = getSelectedItems();

    for (auto item : selectedItems) {
        TableDataView *data = dynamic_cast<TableDataView *>(item);

        if (data == nullptr)
            continue;

        data->setActivateFunctionType(type);
    }
}

int TableDataView::getLossFunctionType() {
    return presentor->getLossFunctionType();
}

void TableDataView::onLossFunctionTypeChanged(int type) {
    QList<QGraphicsItem *> selectedItems = getSelectedItems();

    for (auto item : selectedItems) {
        TableDataView *data = dynamic_cast<TableDataView *>(item);

        if (data == nullptr)
            continue;

        data->setLossFunctionType(type);
    }
}

void TableDataView::setLossFunctionType(int type) {
    presentor->setLossFunctionType(LossFunctionType (type));
}

void TableDataView::setActivateFunctionType(int type) {
    presentor->setActivateFunctionType(type);
}

void TableDataView::openSetsDialog() {

}

TableDataView::~TableDataView() {
    removeArrows();

    delete presentor;
    presentor = nullptr;
}
