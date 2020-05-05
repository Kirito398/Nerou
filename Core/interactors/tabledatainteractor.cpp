#include "tabledatainteractor.h"

#include "listeners/tabledatapresentorlistener.h"
#include "interfaces/repositoryinterface.h"
#include "models/tabledatasetmodel.h"
#include "interfaces/weightinterface.h"

TableDataInteractor::TableDataInteractor() : NeuronInteractor(Data)
{
    view = nullptr;
    repository = nullptr;
    activateFunctionType = Sigmoid;
    lossFunctionType = CrossEntropy;
    dataSet = new TableDataSetModel();
}

void TableDataInteractor::start(unsigned long classNumber, unsigned long iterationNumber) {
    std::vector<std::string> value = dataSet->getTrainingInputSet(iterationNumber);

    for (size_t i = 0; i < outputsSinaps.size(); i++) {
        WeightInterface *weight = dynamic_cast<WeightInterface *>(outputsSinaps.at(i));
        if (weight == nullptr)
            continue;

        weight->sendSignal(std::stod(value[i]));
    }
}

void TableDataInteractor::onInputSignalChanged() {

}

void TableDataInteractor::onDeltaValueChanged() {

}

double TableDataInteractor::getLoss() {

}

unsigned int TableDataInteractor::getAnswer() {

}

std::vector<std::vector<std::string>> TableDataInteractor::loadTableValue(std::string path) {
    return repository->loadTableValue(path);
}

void TableDataInteractor::removeSinaps(unsigned long sinapsID) {
    NeuronInteractor::removeSinaps(sinapsID);
}

void TableDataInteractor::clean() {

}

void TableDataInteractor::setView(TableDataPresentorListener *listener) {
    view = listener;
    view->updatePosition(posX, posY);
}

void TableDataInteractor::setRepository(RepositoryInterface *repository) {
    this->repository = repository;
}

void TableDataInteractor::setPosition(double x, double y) {
    posX = x;
    posY = y;

    if (view != nullptr)
        view->updatePosition(posX, posY);
}

void TableDataInteractor::deleteNeuron() {
    removeNeuron();
}

unsigned long TableDataInteractor::getID() {
    return id;
}

void TableDataInteractor::setLossFunctionType(LossFunctionType type) {
    lossFunctionType = type;
}

LossFunctionType TableDataInteractor::getLossFunctionType() {
    return lossFunctionType;
}

void TableDataInteractor::setActivateFunctionType(int type) {
    activateFunctionType = ActivateFunctionType(type);
}

int TableDataInteractor::getActivateFunctiontype() {
    return activateFunctionType;
}

unsigned long TableDataInteractor::getClassNumber() {
    return 1;
}

unsigned long TableDataInteractor::getTrainingIterationNumber() {
    return dataSet->getTrainingIterationNumber();
}

std::string TableDataInteractor::getDataSetMainPath() {
    return dataSet->getMainPath();
}

void TableDataInteractor::setDataSetMainPath(std::string path) {
    dataSet->setMainPath(path);
}

void TableDataInteractor::addTestingInputSet(std::vector<std::string> set) {
    dataSet->addTestingInputSet(set);
}

void TableDataInteractor::addTestingTargetSet(std::vector<std::string> set) {
    dataSet->addTestingTargetSet(set);
}

void TableDataInteractor::addTrainingInputSet(std::vector<std::string> set) {
    dataSet->addTrainingInputSet(set);
}

void TableDataInteractor::addTrainingTargetSet(std::vector<std::string> set) {
    dataSet->addTrainingTargetSet(set);
}

void TableDataInteractor::setInputsTitles(std::vector<std::string> titles) {
    dataSet->setInputsTitles(titles);
}

void TableDataInteractor::setTargetTitles(std::vector<std::string> titles) {
    dataSet->setTargetsTitles(titles);
}

std::vector<std::string> TableDataInteractor::getInputsTitles() {
    return dataSet->getInputTitles();
}

std::vector<std::string> TableDataInteractor::getTargetTitles() {
    return dataSet->getTargetTitles();
}

void TableDataInteractor::clearDataSet() {
    dataSet->clear();
}

