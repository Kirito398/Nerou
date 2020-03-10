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
    createdNeuronCount = 0;
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
    for (auto sinaps : sinapsList)
        sinaps->init();
}

void MainInteractor::createNewPerceptron() {
    PerceptronInteractor *newPerceptron = new PerceptronInteractor();

    createdNeuronCount++;
    newPerceptron->setID(createdNeuronCount);

    neuronsList.push_back(newPerceptron);
    view->onNewPerceptronAdded(newPerceptron);
}

void MainInteractor::createNewData(double x, double y) {
    DataInteractor *newData = new DataInteractor();

    createdNeuronCount++;
    newData->setID(createdNeuronCount);
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
        return newCore;
    }

    delete newCore;
    return nullptr;
}

NeuronInteractor *MainInteractor::findNeuron(unsigned long id) {
    for (auto neuron : neuronsList)
        if (neuron->getID() == id)
            return neuron;
    return nullptr;
}

//SinapsModel *MainInteractor::makeSinaps(ModelItem *inputItem, ModelItem *outputItem) {
//    SinapsModel::SinapsType type;

//    if (inputItem->getType() == ModelItem::Perceptron || inputItem->getType() == ModelItem::Data) {
//        type = SinapsModel::Weigth;
//    } else {
//        type = SinapsModel::Core;
//    }

//    SinapsModel *sinaps = sinapsFactory.create(inputItem, outputItem, type);

//    inputItem->addOutputSinaps(sinaps);
//    outputItem->addInputSinaps(sinaps);

//    sinapsModelsList.push_back(sinaps);

//    return sinaps;
//}

//void MainInteractor::removeItem(MoveItemInterface *item) {
//    for(unsigned long i = 0; i < itemsList.size(); i++) {
//        if (itemsList.at(i)->getListener() == item) {
//            itemsList.erase(itemsList.begin() + i);
//            vector<ModelItem *>(itemsList).swap(itemsList);
//            break;
//        }
//    }
//}

//void MainInteractor::removeSinaps(SinapsModel *item) {
//    for(unsigned long i = 0; i < sinapsModelsList.size(); i++) {
//        if (sinapsModelsList.at(i) == item) {
//            sinapsModelsList.erase(sinapsModelsList.begin() + i);
//            vector<SinapsModel *>(sinapsModelsList).swap(sinapsModelsList);
//            break;
//        }
//    }
//}

MainInteractor * MainInteractor::instance;
