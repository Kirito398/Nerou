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
    isAnimateTrainingProcessEnabled = true;
    activateFunctionType = Sigmoid;
    inputSignalCount = 0;
}

double NeuronInteractor::activateFunction(double value) {
    double result = value;

        switch(activateFunctionType) {
            case Sigmoid: { result = sigmoidFunction(value); break; }
            case Tanh: { result = tanhFunction(value); break; }
            case ReLU: { result = reluFunction(value); break; }
            case Softmax: { result = value; break; }
        }

        return result;
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
    double result = value;

        switch(activateFunctionType) {
            case Sigmoid: { result = reSigmoidFunction(value); break; }
            case Tanh: { result = reTanhFunction(value); break; }
            case ReLU: { result = reReluFunction(value); break; }
            case Softmax: { result = 1; break; }
        }

        return result;
}

double NeuronInteractor::sigmoidFunction(double value) {
    return 1.0 / (1.0 + exp(-value));
}

double NeuronInteractor::tanhFunction(double value) {
    return (exp(2 * value) - 1) / (exp(2 * value) + 1);
}

double NeuronInteractor::reluFunction(double value) {
    return value < 0 ? 0 : value;
}

std::vector<double> NeuronInteractor::softmaxFunction(std::vector<double> values) {
    std::vector<double> temp;
    double sum = 0;

    for (auto value : values)
        sum += exp(value);

    for (auto value : values)
        temp.push_back(exp(value) / sum);

    return temp;
}

double NeuronInteractor::reSigmoidFunction(double value) {
    return (1.0 - value) * value;
}

double NeuronInteractor::reTanhFunction(double value) {
    return 1.0 - pow(value, 2);
}

double NeuronInteractor::reReluFunction(double value) {
    return value < 0 ? 0 : 1;
}

double NeuronInteractor::reSoftmaxFunction(double value) {
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

    return value;
}

std::vector<std::vector<std::vector<double> > > NeuronInteractor::normalization(std::vector<std::vector<std::vector<double> > > value) {
    for (auto color : value)
        normalization(color);

    return value;
}

double NeuronInteractor::mseFunction(std::vector<double> answer, std::vector<double> mark) {
    unsigned int size = answer.size();
    double sum = 0;

    for (unsigned int i = 0; i < size; i++)
        sum += pow(answer[i] - mark[i], 2.0);

    return sum / size;
}

double NeuronInteractor::crossEntropyFunction(std::vector<double> answer, std::vector<double> mark) {
    unsigned int size = answer.size();
    double sum = 0;

    for (unsigned int i = 0; i < size; i++)
        sum += -(mark[i] * log(answer[i]));

    return sum / size;
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

void NeuronInteractor::setAnimateTrainingProcessEnable(bool enable) {
    isAnimateTrainingProcessEnabled = enable;
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
