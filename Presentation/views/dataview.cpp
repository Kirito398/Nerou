#include "dataview.h"

#include <QPainter>
#include <QThread>
#include <QDialog>
#include <QGroupBox>
#include <QBoxLayout>

#include "presenters/datapresentor.h"
#include "dialogs/datasetsdialog.h"
#include "dialogs/dataparametersdialog.h"

DataView::DataView(DataInteractorListener *listener, QObject *parent) : MovingView(Data, parent)
{
    makePolygon();

    propertiesBox = nullptr;

    presentor = new DataPresentor();
    presentor->setView(this);

    if (listener != nullptr) {
        presentor->setInteractor(listener);
        setToolTip("Neuron_" + QString::number(presentor->getID()));
    }

    bounding = QRectF (-30, -30, 60, 60);
    imageBounding = QRectF(-30, -30, 30, 30);

    brushColor = QColor(115, 255, 227);

    setsDialog = nullptr;
    parametersDialog = nullptr;
}

void DataView::updatePosition(double x, double y) {
    this->setPos(x, y);
    updateArrowsPosition();
}

void DataView::setPosition(QPointF position) {
    presentor->setPosition(position.x(), position.y());
}

void DataView::setImage(QString path) {
    image = QImage(path);
    updateItem(this);
}

unsigned long DataView::getID() {
    return presentor->getID();
}

QPixmap DataView::getItemIcon() const {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.setPen(Qt::black);
    painter.setBrush(brushColor);
    painter.translate(50, 50);
    painter.drawRect(bounding);

    return pixmap;
}

QPolygonF DataView::getPolygon() {
    return polygon;
}

QRectF DataView::boundingRect() const {
    return bounding;
}

void DataView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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

void DataView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event)

    openSetsDialog();
}

QBoxLayout *DataView::getPropertiesLayout() {
    if (parametersDialog == nullptr)
        parametersDialog = new DataParametersDialog(this);

    return parametersDialog->getMainLayout();
}

void DataView::onParametersUpdated() {
    QStringList trainingList, testingList, neuronsIDs;

    setsDialog->getParameters(&trainingList, &testingList, &neuronsIDs);
    presentor->updateParameters(trainingList, testingList, neuronsIDs);
}

bool DataView::isOutputNeuron() {
    return false;
}

QStringList DataView::getOutputsNeuronsList() {
    return outputsNeuronsList();
}

void DataView::makePolygon() {
    polygon << bounding.topLeft() << bounding.topRight() << bounding.bottomRight() << bounding.bottomLeft() << bounding.topLeft();
}

void DataView::setLossFunctionType(int type) {
    presentor->setLossFunctionType(LossFunctionType (type));
}

void DataView::setActivateFunctionType(int type) {
    presentor->setActivateFunctionType(type);
}

void DataView::setUseColorModeEnable(bool enable) {
    presentor->setUseColorModeEnable(enable);
}

void DataView::onLossFunctionTypeChanged(int type) {
    QList<QGraphicsItem *> selectedItems = getSelectedItems();

    for (auto item : selectedItems) {
        DataView *data = dynamic_cast<DataView *>(item);

        if (data == nullptr)
            continue;

        data->setLossFunctionType(type);
    }
}

void DataView::onActivateFunctionTypeChanged(int type) {
    QList<QGraphicsItem *> selectedItems = getSelectedItems();

    for (auto item : selectedItems) {
        DataView *data = dynamic_cast<DataView *>(item);

        if (data == nullptr)
            continue;

        data->setActivateFunctionType(type);
    }
}

void DataView::onUseColorModeEnableChanged(bool enable) {
    QList<QGraphicsItem *> selectedItems = getSelectedItems();

    for (auto item : selectedItems) {
        DataView *data = dynamic_cast<DataView *>(item);

        if (data == nullptr)
            continue;

        data->setUseColorModeEnable(enable);
    }
}

bool DataView::getUseColorModeEnable() {
    return presentor->getUseColorModeEnable();
}

int DataView::getLossFunctionType() {
    return presentor->getLossFunctionType();
}

int DataView::getActivateFunctionType() {
    return presentor->getActivateFunctionType();
}

void DataView::openSetsDialog() {
    if (setsDialog == nullptr) {
        setsDialog = new DataSetsDialog(this, presentor);
        connect(setsDialog, &QDialog::accept, this, &DataView::onParametersUpdated);
        connect(setsDialog, &DataSetsDialog::onApplied, this, &DataView::onParametersUpdated);
    }


    QStringList trainingList, testingList, neuronsIDs;
    presentor->getParameters(&trainingList, &testingList, &neuronsIDs);

    setsDialog->updateParameters(trainingList, testingList, neuronsIDs);
    setsDialog->show();
}

DataView::~DataView() {
    removeArrows();

    delete presentor;
    presentor = nullptr;
}
