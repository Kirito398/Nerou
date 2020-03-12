#include "datapresentor.h"

#include <QDir>

#include "listeners/datainteractorlistener.h"
#include "listeners/dataviewlistener.h"

DataPresentor::DataPresentor()
{
    interactor = nullptr;
}

void DataPresentor::setView(DataViewListener *listener) {
    view = listener;
}

void DataPresentor::setInteractor(DataInteractorListener *listener) {
    interactor = listener;
    interactor->setView(this);

    QDir dir("TrainSet");
    QString mainPath = "TrainSet/0/";
    dir.setPath(mainPath);
    QStringList listPath = dir.entryList(QStringList("*.jpg"));

    std::vector<std::string> classList;

    for (auto path : listPath) {
        classList.push_back((mainPath + path).toStdString());
    }

    interactor->addClass(classList);
}

void DataPresentor::updatePosition(double x, double y) {
    view->updatePosition(x, y);
}

void DataPresentor::setImage(std::string path) {
    view->setImage(QString::fromStdString(path));
}

void DataPresentor::setPosition(double x, double y) {
    interactor->setPosition(x, y);
}

unsigned long DataPresentor::getID() {
    return interactor->getID();
}

DataPresentor::~DataPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();
}
