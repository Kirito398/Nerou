#include "tabledatainteractor.h"

#include "listeners/tabledatapresentorlistener.h"
#include "interfaces/repositoryinterface.h"
#include "models/tabledatasetmodel.h"
#include "interfaces/weightinterface.h"

#include <math.h>

TableDataInteractor::TableDataInteractor() : NeuronInteractor(Data)
{
    view = nullptr;
    repository = nullptr;
    activateFunctionType = Sigmoid;
    lossFunctionType = MSE;
    dataSet = new TableDataSetModel();
    currentAnswer = 0;
    currentLoss = 0;
    epsilon = 0.4;
}

void TableDataInteractor::start(unsigned long classNumber, unsigned long iterationNumber) {
    std::vector<double> value = makeNormalize(dataSet->getTrainingInputSet(iterationNumber), dataSet->getTrainingInputsMax(), dataSet->getTrainingInputsMin());
    currentMark = makeNormalize(dataSet->getTrainingTargetSet(iterationNumber), dataSet->getTrainingTargetsMax(), dataSet->getTrainingTargetsMin());
    currentAnswer = classNumber;

    for (size_t i = 0; i < outputsSinaps.size(); i++) {
        WeightInterface *weight = dynamic_cast<WeightInterface *>(outputsSinaps.at(i));
        if (weight == nullptr)
            continue;

        weight->sendSignal(value[i]);
    }
}

std::vector<double> TableDataInteractor::makeNormalize(std::vector<double> value, std::vector<double> max, std::vector<double> min) {
    std::vector<double> normalizeValue;
    size_t size = value.size();

    for (size_t i = 0; i < size; i++)
        normalizeValue.push_back(normalization(value[i], max[i], min[i]));

    return normalizeValue;
}

void TableDataInteractor::onInputSignalChanged() {
    inputSignalCount++;

    if (inputSignalCount != inputsSinaps.size())
        return;

    calculateInputSignal();
    calculateLoss();
    calculateDelta();
    sendDelta();
    inputSignalCount = 0;
}

void TableDataInteractor::calculateInputSignal() {
    inputSignal.clear();

    for (auto sinaps : inputsSinaps) {
        if (sinaps->getType() != sinaps->Weigth)
            continue;

        inputSignal.push_back(static_cast<WeightInterface *>(sinaps)->getValue());
    }
}

void TableDataInteractor::calculateLoss() {
    switch (lossFunctionType) {
    case MSE: {currentLoss = mseFunction(inputSignal, currentMark); break;}
    case CrossEntropy: {currentLoss = crossEntropyFunction(inputSignal, currentMark); break;}
    }
}

void TableDataInteractor::calculateDelta() {
    currentDelta.clear();

    for (unsigned int i = 0; i < inputSignal.size(); i++)
        currentDelta.push_back(inputSignal[i] - currentMark[i]);
}

void TableDataInteractor::sendDelta() {
    for (unsigned int i = 0; i < inputsSinaps.size(); i++) {
        if (inputsSinaps[i]->getType() == inputsSinaps[i]->Weigth) {
            WeightInterface *weight = static_cast<WeightInterface *>(inputsSinaps[i]);
            weight->sendDelta(currentDelta[i]);
        }
    }
}

void TableDataInteractor::onDeltaValueChanged() {

}

double TableDataInteractor::getLoss() {
    return currentLoss;
}

unsigned int TableDataInteractor::getAnswer() {
    for (auto delta : currentDelta)
        if (fabs(delta) > epsilon)
            currentAnswer++;

    return currentAnswer;
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

void TableDataInteractor::addTestingInputSet(std::vector<double> set) {
    dataSet->addTestingInputSet(set);
}

void TableDataInteractor::addTestingTargetSet(std::vector<double> set) {
    dataSet->addTestingTargetSet(set);
}

void TableDataInteractor::addTrainingInputSet(std::vector<double> set) {
    dataSet->addTrainingInputSet(set);
}

void TableDataInteractor::addTrainingTargetSet(std::vector<double> set) {
    dataSet->addTrainingTargetSet(set);
}

void TableDataInteractor::setInputsTitles(std::vector<std::string> titles) {
    dataSet->setInputsTitles(titles);
}

void TableDataInteractor::setTargetTitles(std::vector<std::string> titles, std::vector<unsigned long> outputsNeuronsID) {
    dataSet->setTargetsTitles(titles);

    for (size_t i = 0; i < titles.size(); i++)
        makeLearningSinaps(outputsNeuronsID[i], id);
}

std::vector<std::string> TableDataInteractor::getInputsTitles() {
    return dataSet->getInputTitles();
}

std::vector<std::string> TableDataInteractor::getTargetTitles() {
    return dataSet->getTargetTitles();
}

void TableDataInteractor::clearDataSet() {
    dataSet->clear();

    std::vector<SinapsInteractor *> sinaps(inputsSinaps);
    for(unsigned long i = 0; i < sinaps.size(); i++)
        sinaps.at(i)->removeSinaps();
}

size_t TableDataInteractor::getOutputNeuronsNumber() {
    return outputsSinaps.size();
}

