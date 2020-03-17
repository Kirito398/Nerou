#include "datapresentor.h"

#include <QDir>
#include <QSize>

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
}

void DataPresentor::setPathsList(QStringList pathsList, bool isTrainingSet) {
    interactor->clearPathsList();

    if (pathsList.isEmpty())
        return;

    QStringList entryList;
    entryList << "*.jpg" << "*.png";

    for (auto mainPath : pathsList) {
        QDir dir(mainPath);
        QStringList listPath = dir.entryList(entryList);
        std::vector<std::string> classList;

        for (auto path : listPath)
            classList.push_back((mainPath + "/" + path).toStdString());

        //interactor->addClass(classList, isTrainingSet);
    }
}

void DataPresentor::setImageSize(QSize size) {
    interactor->setSize(size.height(), size.width());
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
