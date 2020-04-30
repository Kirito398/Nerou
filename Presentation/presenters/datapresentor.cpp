#include "datapresentor.h"

#include <QDir>
#include <QSize>

#include "listeners/datainteractorlistener.h"
#include "listeners/dataviewlistener.h"
#include "models/classmodel.h"
#include "interfaces/repositoryinterface.h"

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

    repository = interactor->getRepository();
}

void DataPresentor::updateParameters(QStringList trainingList, QStringList testingList, QStringList neuronsIDs) {
    int n = trainingList.size();

    interactor->clearClassList();

    for (int i = 0; i < n; i++) {
        ClassModel model(neuronsIDs[i].split("_")[1].toDouble());
        model.setTrainingMainPath(trainingList[i].toStdString());
        model.setTestingMainPath(testingList[i].toStdString());
        model.setTrainingPathsList(repository->getPaths(trainingList[i].toStdString()));
        model.setTestingPathslist(repository->getPaths(testingList[i].toStdString()));

        interactor->addClass(model);
    }
}

void DataPresentor::getParameters(QStringList *trainingList, QStringList *testingList, QStringList *neuronsIDs) {
    unsigned long classNumber = interactor->getClassNumber();

    for (unsigned long i = 0; i < classNumber; i++) {
        ClassModel model = interactor->getClass(i);

        trainingList->append(QString::fromStdString(model.getTrainingMainPath()));
        testingList->append(QString::fromStdString(model.getTestingMainPath()));
        neuronsIDs->append("Neuron_" + QString::number(model.getNeuronID()));
    }
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

RepositoryInterface *DataPresentor::getRepository() {
    return repository;
}

void DataPresentor::setUseColorModeEnable(bool enable) {
    interactor->setColorModeEnable(enable);
}

bool DataPresentor::getUseColorModeEnable() {
    return interactor->getColorModeEnable();
}

void DataPresentor::setActivateFunctionType(int type) {
    interactor->setActivateFunctionType(type);
}

int DataPresentor::getActivateFunctionType() {
    return interactor->getActivateFunctiontype();
}

void DataPresentor::setLossFunctionType(LossFunctionType type) {
    interactor->setLossFunctionType(type);
}

LossFunctionType DataPresentor::getLossFunctionType() {
    return interactor->getLossFunctionType();
}

DataPresentor::~DataPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();
}
