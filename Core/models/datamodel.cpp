#include "datamodel.h"

#include "models/weightmodel.h"

DataModel::DataModel(MoveItemInterface *listener) : ModelItem(listener, VectorData)
{

}

void DataModel::sendData() {
    dynamic_cast<WeightModel *>(outputItems.at(0))->sendSignal(1.0);
}

void DataModel::onInputSignalChanged() {

}
