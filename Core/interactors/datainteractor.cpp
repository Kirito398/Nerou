#include "datainteractor.h"

#include "listeners/datapresentorlistener.h"
#include "interfaces/coreinterface.h"
#include "interfaces/weightinterface.h"
#include "interfaces/repositoryinterface.h"
#include "models/classmodel.h"
#include "models/datamodel.h"

#include <math.h>

DataInteractor::DataInteractor() : NeuronInteractor(Data)
{
    view = nullptr;
    repository = nullptr;
    inputSignalCount = 0;
    inputDeltaCount = 0;
    currentClass = 0;
    currentLoss = 0.0;
    isColorMode = false;
    activateFunctionType = Softmax;
    lossFunctionType = CrossEntropy;
}

void DataInteractor::start(unsigned long classNumber, unsigned long iterationNumber) {
    if (classList.empty())
        return;

    if (iterationNumber >= classList[classNumber].getTrainingPathsList().size())
        return;

    currentClass = classNumber;

    view->setImage(classList[classNumber].getTrainingPathsList()[iterationNumber]);

    if (isColorMode) {
        colorValue = repository->loadColorValue(classList[classNumber].getTrainingPathsList()[iterationNumber]);
        colorValue = normalization(colorValue);
        colorsToValue();
    } else {
        value.clear();
        value = normalization(repository->loadValue(classList[classNumber].getTrainingPathsList()[iterationNumber]));
    }

    sendData();
    colorValue.clear();
    value.clear();
}

void DataInteractor::sendData() {
    if (outputsSinaps.empty())
        return;

    unsigned int size = isColorMode ? colorValue[0][0].size() * colorValue[0].size() * colorValue.size() : value[0].size() * value.size();
    unsigned long weightCounter = 0;
    unsigned long coreCounter = 0;

    double *temp;
    if (isColorMode)
        temp = colorsToValue();
    else
        temp = valueToLine();


    for (auto sinaps : outputsSinaps) {
        if (sinaps->getType() == sinaps->Weigth) {
            dynamic_cast<WeightInterface *>(sinaps)->sendSignal(temp[weightCounter++ % size]);
            continue;
        }

        CoreInterface *core = dynamic_cast<CoreInterface *>(sinaps);


        if (isColorMode)
            core->sendSignal(colorValue[coreCounter++ % 3]);
        else
            core->sendSignal(value);
    }

    delete [] temp;
}

double *DataInteractor::colorsToValue() {
    unsigned int size = colorValue[0][0].size() * colorValue[0].size();
    double *value = new double[size * colorValue.size()];

    for (unsigned int i = 0; i < colorValue.size(); i++) {
        for (unsigned int j = 0; j < colorValue[i].size(); j++) {
            for (unsigned int k = 0; k < colorValue[i][j].size(); k++) {
                value[i*size+j] = colorValue[i][j][k];
            }
        }
    }

    return value;
}

double *DataInteractor::valueToLine() {
    unsigned int size = value.size() * value[0].size();

    double *line = new double[size];

    for (unsigned int i = 0; i < value.size(); i++) {
        for (unsigned int j = 0; j < value[i].size(); j++) {
            line[i * value[i].size() + j] = value[i][j];
        }
    }

    return line;
}

void DataInteractor::addClass(ClassModel model) {
    classList.push_back(model);

    makeLearningSinaps(model.getNeuronID(), id);
}

ClassModel DataInteractor::getClass(unsigned long id) {
    return classList[id];
}

void DataInteractor::clearClassList() {
    classList.clear();

    std::vector<SinapsInteractor *> sinaps(inputsSinaps);
    for(unsigned long i = 0; i < sinaps.size(); i++)
        sinaps.at(i)->removeSinaps();
}

void DataInteractor::setRepository(RepositoryInterface *repository) {
    this->repository = repository;
}

unsigned long DataInteractor::getClassNumber() {
    return classList.size();
}

unsigned long DataInteractor::getTrainingIterationNumber() {
    unsigned long number = 0;

    for (auto item : classList) {
        unsigned long size = item.getTrainingPathsList().size();

        if (size > number)
            number = size;
    }

    return number;
}

void DataInteractor::setView(DataPresentorListener *listener) {
    view = listener;

    view->updatePosition(posX, posY);
}

void DataInteractor::setPosition(double x, double y) {
    posX = x;
    posY = y;

    if (view != nullptr)
        view->updatePosition(posX, posY);
}

unsigned long DataInteractor::getID() {
    return id;
}

void DataInteractor::removeSinaps(unsigned long sinapsID) {
    for (auto sinaps : inputsSinaps) {
        if (sinaps->getID() != sinapsID)
            continue;

        unsigned long neuronID = sinaps->getInputNeuron()->getID();

        for (unsigned long i = 0; i < classList.size(); i++) {
            ClassModel model = classList.at(i);
            if (model.getNeuronID() != neuronID)
                continue;

            classList.erase(classList.begin() + i);
            std::vector<ClassModel>(classList).swap(classList);
            break;
        }
    }

    NeuronInteractor::removeSinaps(sinapsID);
}

void DataInteractor::deleteNeuron() {
    removeNeuron();
}

void DataInteractor::clean() {
    value.clear();
    colorValue.clear();
    view->setImage("");
}

RepositoryInterface *DataInteractor::getRepository() {
    return repository;
}

void DataInteractor::onInputSignalChanged() {
    inputSignalCount++;

    if (inputSignalCount != inputsSinaps.size())
        return;

    calculateInputSignal();
    calculateDelta();
    calculateLoss();
    sendDelta();
    inputSignalCount = 0;
}

void DataInteractor::calculateInputSignal() {
    inputSignal.clear();
    currentMark.clear();

    for (unsigned int i = 0; i < inputsSinaps.size(); i++) {
        if (inputsSinaps[i]->getType() != inputsSinaps[i]->Weigth)
            continue;

        WeightInterface *weight = static_cast<WeightInterface *>(inputsSinaps[i]);
        inputSignal.push_back(weight->getValue());

        if (weight->getInputNeuron()->getID() == classList[currentClass].getNeuronID())
            currentMark.push_back(1.0);
        else
            currentMark.push_back(0.0);
    }

    if (activateFunctionType == Softmax)
        inputSignal = softmaxFunction(inputSignal);
}

void DataInteractor::calculateDelta()  {
    currentDelta.clear();

    for (unsigned int i = 0; i < inputSignal.size(); i++) {
        double delta = 0;

        delta = inputSignal[i] - currentMark[i];

//        if (activateFunctionType == Softmax)
//            delta *= reSoftmaxFunction(inputSignal[i]);

        currentDelta.push_back(delta);
    }
}

void DataInteractor::calculateLoss() {
    switch (lossFunctionType) {
    case MSE: {currentLoss = mseFunction(inputSignal, currentMark); break;}
    case CrossEntropy: {currentLoss = crossEntropyFunction(inputSignal, currentMark); break;}
    }
}

double DataInteractor::mseFunction(std::vector<double> answer, std::vector<double> mark) {
    unsigned int size = answer.size();
    double sum = 0;

    for (unsigned int i = 0; i < size; i++)
        sum += pow(answer[i] - mark[i], 2.0);

    return sum / size;
}

double DataInteractor::crossEntropyFunction(std::vector<double> answer, std::vector<double> mark) {
    unsigned int size = answer.size();
    double sum = 0;

    for (unsigned int i = 0; i < size; i++)
        sum += -(mark[i] * log(answer[i]));

//    for (unsigned int i = 0; i < size; i++)
//        sum += -(mark[i] * log(answer[i]) + (1 - mark[i] * log(1 - answer[i])));

    return sum / size;
}

unsigned int DataInteractor::getAnswer() {
    unsigned int answerNeuronID = inputsSinaps[getMaxIndex(inputSignal)]->getInputNeuron()->getID();

    for (unsigned int i = 0; i < classList.size(); i++)
        if (classList[i].getNeuronID() == answerNeuronID)
            return i;
}

unsigned int DataInteractor::getMaxIndex(std::vector<double> value) {
    unsigned int index = 0;
    double max = value[0];

    for (unsigned int i = 0; i < value.size(); i++) {
        if (max >= value[i])
            continue;

        max = value[i];
        index = i;
    }

    return index;
}

DataModel DataInteractor::getModel() {
    DataModel model;

    model.setX(posX);
    model.setY(posY);
    model.setID(id);
    model.setType(type);
    model.setIsOutput(isOutput);
    model.setClassList(classList);
    model.setIsColorMode(isColorMode);
    model.setActivateFunctionType(activateFunctionType);
    model.setLossFunctionType(lossFunctionType);

    return model;
}

void DataInteractor::updateFromModel(DataModel model) {
    posX = model.getX();
    posY = model.getY();
    id = model.getID();
    type = NeuronType(model.getType());
    isOutput = model.getIsOutput();
    isColorMode = model.getIsColorMode();
    activateFunctionType = ActivateFunctionType (model.getActivateFunctionType());
    lossFunctionType = LossFunctionType (model.getLossFunctionType());

    std::vector<ClassModel> list = model.getClassList();

    for (size_t i = 0; i < list.size(); i++)
        addClass(list.at(i));
}

double DataInteractor::getLoss() {
    return currentLoss;
}

void DataInteractor::sendDelta() {
    for (unsigned int i = 0; i < inputsSinaps.size(); i++) {
        if (inputsSinaps[i]->getType() == inputsSinaps[i]->Weigth) {
            WeightInterface *weight = static_cast<WeightInterface *>(inputsSinaps[i]);
            weight->sendDelta(currentDelta[i]);
        }
    }
}

void DataInteractor::onDeltaValueChanged() {

}
