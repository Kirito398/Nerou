#include "datapresentor.h"

#include "listeners/datainteractorlistener.h"
#include "listeners/dataviewlistener.h"

DataPresentor::DataPresentor()
{

}

void DataPresentor::setView(DataViewListener *listener) {
    view = listener;
}

void DataPresentor::setInteractor(DataInteractorListener *listener) {
    interactor = listener;
}

void DataPresentor::updatePosition(double x, double y) {
    view->updatePosition(x, y);
}

void DataPresentor::setPosition(double x, double y) {
    interactor->setPosition(x, y);
}

unsigned long DataPresentor::getID() {
    return interactor->getID();
}
