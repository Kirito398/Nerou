#include "neuroninteractor.h"

#include "math.h"

#include "interactors/sinapsinteractor.h"
#include "interfaces/maininteractorinterface.h"

NeuronInteractor::NeuronInteractor(NeuronType type)
{
    this->type = type;
    id = 0;
    posX = 0;
    posY = 0;
    isOutput = false;
}

double NeuronInteractor::activateFunction(double value) {
    return 1.0 / (1.0 + exp(-value));
}

void NeuronInteractor::activateFunction(double* value, unsigned int size) {
    for (unsigned int i = 0; i < size; i++)
        value[i] = activateFunction(value[i]);
}

void NeuronInteractor::activateFunction(double** value, unsigned int row, unsigned int column) {
    for (unsigned int i = 0; i < row; i++)
        for (unsigned int j = 0; j < column; j++)
            value[i][j] = activateFunction(value[i][j]);
}

double NeuronInteractor::reActivateFunction(double value) {
    return (1.0 - value) * value;
}

double NeuronInteractor::normalization(double value, double max, double min) {
    return (value - min) / (max - min);
}

std::vector<std::vector<double>> NeuronInteractor::normalization(std::vector<std::vector<double>> value) {
    double max = value[0][0];
    double min = value[0][0];

    for (auto row : value)
        for (auto item : row) {
            if (max < item) max = item;
            if (min > item) min = item;
        }

    for (unsigned int i = 0; i < value.size(); i++)
        for (unsigned int j = 0; j < value[i].size(); j++)
            value[i][j] = normalization(value[i][j], max, min);

//    for (auto row : value)
//        for (auto item : row)
//            item = normalization(item, max, min);

    return value;
}

std::vector<std::vector<std::vector<double> > > NeuronInteractor::normalization(std::vector<std::vector<std::vector<double> > > value) {
    for (auto color : value)
        normalization(color);

    return value;
}

void NeuronInteractor::makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID) {
    for (auto sinaps : inputsSinaps)
        if (sinaps->getOutputNeuron()->getID() == learningNeuronID)
            return;

    interactor->makeLearningSinaps(learningNeuronID, dataNeuronID);
}

void NeuronInteractor::setID(unsigned long id) {
    this->id = id;
}

unsigned long NeuronInteractor::getID() {
    return id;
}

void NeuronInteractor::setInteractor(MainInteractorInterface *interface) {
    interactor = interface;
}

bool NeuronInteractor::addArrow(SinapsInteractor* arrow) {
    if (isArrowAlreadyAdded(arrow))
        return false;

    SinapsListener *inputNeuron = arrow->getInputNeuron();
    SinapsListener *outputNeuron = arrow->getOutputNeuron();

    if (inputNeuron == this)
        outputsSinaps.push_back(arrow);

    if (outputNeuron == this)
        inputsSinaps.push_back(arrow);

    return true;
}

bool NeuronInteractor::isArrowAlreadyAdded(SinapsInteractor* arrow) {
    for (auto item : outputsSinaps)
        if (arrow->getInputNeuron() == item->getInputNeuron() && arrow->getOutputNeuron() == item->getOutputNeuron())
            return true;

    for (auto item : inputsSinaps)
        if (arrow->getInputNeuron() == item->getInputNeuron() && arrow->getOutputNeuron() == item->getOutputNeuron())
            return true;

    return false;
}

NeuronType NeuronInteractor::getType() {
    return type;
}

bool NeuronInteractor::isOutputNeuron() {
    return isOutput;
}

void NeuronInteractor::isOutputNeuronEnable(bool enable) {
    isOutput = enable;
}

void NeuronInteractor::removeSinaps(unsigned long sinapsID) {
    for (unsigned long i = 0; i < inputsSinaps.size(); i++) {
        if (inputsSinaps.at(i)->getID() == sinapsID) {
            inputsSinaps.erase(inputsSinaps.begin() + i);
            std::vector<SinapsInteractor *>(inputsSinaps).swap(inputsSinaps);
            return;
        }
    }

    for (unsigned long i = 0; i < outputsSinaps.size(); i++) {
        if (outputsSinaps.at(i)->getID() == sinapsID) {
            outputsSinaps.erase(outputsSinaps.begin() + i);
            std::vector<SinapsInteractor *>(outputsSinaps).swap(outputsSinaps);
            return;
        }
    }
}

void NeuronInteractor::removeSinapses() {
    std::vector<SinapsInteractor *> input(inputsSinaps);
    std::vector<SinapsInteractor *> output(outputsSinaps);

    for (auto sinaps : input)
        sinaps->removeSinaps();

    for (auto sinaps : output)
        sinaps->removeSinaps();
}

void NeuronInteractor::removeNeuron() {
    interactor->removeNeuron(id);
}

NeuronInteractor::~NeuronInteractor() {
    removeSinapses();
}
