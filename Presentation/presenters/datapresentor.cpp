#include "datapresentor.h"

#include <QDir>
#include <QSize>

#include "listeners/datainteractorlistener.h"
#include "listeners/dataviewlistener.h"
#include "models/classmodel.h"

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

void DataPresentor::updateParameters(QStringList trainingList, QStringList testingList, QStringList neuronsIDs) {
    int n = trainingList.size();

    interactor->clearClassList();

    for (int i = 0; i < n; i++) {
        ClassModel model(neuronsIDs[i].split("_")[1].toDouble());
        model.setTrainingPathsList(getPaths(trainingList[i]));
        model.setTestingPathslist(getPaths(testingList[i]));

        interactor->addClass(model);
    }
}

std::vector<std::string> DataPresentor::getPaths(QString mainPath) {
    std::vector<std::string> list;

    if (mainPath.isEmpty())
        return list;

    QDir dir(mainPath);
    QStringList entryList;
    entryList << "*.jpg" << "*.png";

    QStringList listPaths = dir.entryList(entryList);

    for (auto path : listPaths)
        list.push_back((mainPath + path).toStdString());

    return list;
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
