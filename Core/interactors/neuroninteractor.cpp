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

double NeuronInteractor::normalization(double value, double max, double min) {
    return (value - min) / (max - min);
}

void NeuronInteractor::normalization(double* value, unsigned int size) {
    double max = value[0];
    double min = value[0];

    for (unsigned int i = 0; i < size; i++) {
        if (max < value[i])
            max = value[i];

        if (min > value[i])
            min = value[i];
    }

    for (unsigned int i = 0; i < size; i++)
        value[i] = normalization(value[i], max, min);
}

void NeuronInteractor::normalization(double** value, unsigned int row, unsigned int column) {
    for (unsigned long i = 0; i < row; i++)
        normalization(value[i], column);
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
    for (auto sinaps : inputsSinaps)
        delete sinaps;

    for (auto sinaps : outputsSinaps)
        delete sinaps;
}

void NeuronInteractor::removeNeuron() {
    interactor->removeNeuron(id);
}

NeuronInteractor::~NeuronInteractor() {
    removeSinapses();
}
