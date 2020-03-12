#include "maininteractor.h"

#include "interactors/neuroninteractor.h"
#include "interactors/sinapsinteractor.h"
#include "interactors/datainteractor.h"
#include "interactors/perceptroninteractor.h"
#include "interactors/weightinteractor.h"
#include "interactors/coreinteractor.h"
#include "listeners/mainpresentorlistener.h"

MainInteractor::MainInteractor()
{
    createdItemsCounter = 0;
}

MainInteractor* MainInteractor::getInstance() {
    if (instance == nullptr)
        instance = new MainInteractor();
    return instance;
}

void MainInteractor::setView(MainPresentorListener *listener) {
    view = listener;
}

void MainInteractor::run() {
    if (dataList.empty())
        return;

    for (auto sinaps : sinapsList)
        sinaps->init();

    unsigned long classNumber = dataList.at(0)->getClassNumber();
    unsigned long iterationNumber = dataList.at(0)->getIterationNumber();

    for (unsigned long i = 0; i < classNumber; i++) {
        for (unsigned long j = 0; j < iterationNumber; j++) {
            for (auto neuron : dataList) {
                neuron->start(i, j);
            }
        }
    }
}

void MainInteractor::createNewPerceptron(double x, double y) {
    PerceptronInteractor *newPerceptron = new PerceptronInteractor();

    newPerceptron->setID(++createdItemsCounter);
    newPerceptron->setInteractor(this);
    newPerceptron->setPosition(x, y);

    neuronsList.push_back(newPerceptron);
    view->onNewPerceptronAdded(newPerceptron);
}

void MainInteractor::createNewData(double x, double y) {
    DataInteractor *newData = new DataInteractor();

    newData->setID(++createdItemsCounter);
    newData->setInteractor(this);
    newData->setPosition(x, y);

    neuronsList.push_back(newData);
    dataList.push_back(newData);
    view->onNewDataAdded(newData);
}

ArrowInteractorListener *MainInteractor::createNewWeight(unsigned long inputID, unsigned long outputID) {
    NeuronInteractor *inputNeuron = findNeuron(inputID);
    NeuronInteractor *outputNeuron = findNeuron(outputID);

    WeightInteractor *newWeight = new WeightInteractor(inputNeuron, outputNeuron);

    if (inputNeuron->addArrow(newWeight) && outputNeuron->addArrow(newWeight)) {
        sinapsList.push_back(newWeight);
        newWeight->setInteractor(this);
        newWeight->setID(++createdItemsCounter);
        return newWeight;
    }

    delete newWeight;
    return nullptr;
}

ArrowInteractorListener *MainInteractor::createNewCore(unsigned long inputID, unsigned long outputID) {
    NeuronInteractor *inputNeuron = findNeuron(inputID);
    NeuronInteractor *outputNeuron = findNeuron(outputID);

    CoreInteractor *newCore = new CoreInteractor(inputNeuron, outputNeuron);

    if (inputNeuron->addArrow(newCore) && outputNeuron->addArrow(newCore)) {
        sinapsList.push_back(newCore);
        newCore->setInteractor(this);
        newCore->setID(++createdItemsCounter);
        return newCore;
    }

    delete newCore;
    return nullptr;
}

void MainInteractor::removeNeuron(unsigned long neuronID) {
    NeuronInteractor *neuron = nullptr;

    for (unsigned long i = 0; i < dataList.size(); i++) {
        neuron = dataList.at(i);

        if (neuron->getID() == neuronID) {
            dataList.erase(dataList.begin() + i);
            std::vector<DataInteractor *>(dataList).swap(dataList);
            neuron = nullptr;
            break;
        }
    }

    for (unsigned long i = 0; i < neuronsList.size(); i++) {
        neuron = neuronsList.at(i);

        if (neuron->getID() == neuronID) {
            neuronsList.erase(neuronsList.begin() + i);
            std::vector<NeuronInteractor *>(neuronsList).swap(neuronsList);

            delete neuron;
            neuron = nullptr;
            break;
        }
    }
}

void MainInteractor::removeSinaps(unsigned long sinapsID) {
    SinapsInteractor *sinaps = nullptr;

    for (unsigned long i = 0; i < sinapsList.size(); i++) {
        sinaps = sinapsList.at(i);

        if (sinaps->getID() == sinapsID) {
            sinapsList.erase(sinapsList.begin() + i);
            std::vector<SinapsInteractor *>(sinapsList).swap(sinapsList);

            delete sinaps;
            sinaps = nullptr;
            break;
        }
    }
}

NeuronInteractor *MainInteractor::findNeuron(unsigned long id) {
    for (auto neuron : neuronsList)
        if (neuron->getID() == id)
            return neuron;
    return nullptr;
}

MainInteractor * MainInteractor::instance;
