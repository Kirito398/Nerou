#include "maininteractor.h"

#include "interactors/neuroninteractor.h"
#include "interactors/sinapsinteractor.h"
#include "interactors/datainteractor.h"
#include "interactors/perceptroninteractor.h"
#include "interactors/weightinteractor.h"
#include "interactors/coreinteractor.h"
#include "listeners/mainpresentorlistener.h"
#include "interfaces/repositoryinterface.h"
#include "models/datamodel.h"
#include "models/perceptronmodel.h"
#include "models/classmodel.h"
#include "models/weightmodel.h"

MainInteractor::MainInteractor(RepositoryInterface *repository)
{
    this->repository = repository;
    repository->setInteractor(this);
    createdItemsCounter = 0;

    clearProcessParameters();
}

MainInteractor* MainInteractor::getInstance(RepositoryInterface *repository) {
    if (instance == nullptr)
        instance = new MainInteractor(repository);
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
    unsigned long iterationNumber = dataList.at(0)->getTrainingIterationNumber();
    unsigned long neuronNumber = dataList.size();
    unsigned long epohNumber = 5;

    view->onTrainingStarted(iterationNumber, epohNumber);

    for (unsigned long e = 0; e < epohNumber; e++) {
        view->onEpohChanged(e + 1);

        for (unsigned long j = pausedIterationNumber; j < iterationNumber; j++) {
            view->onIterationChanged(j + 1);

            for (unsigned long i = pausedClassNumber; i < classNumber; i++) {
                for (unsigned long k = pausedNeuronNumber; k < neuronNumber; k++) {
                    if (isStopped) {
                        onProcessStopped();
                        return;
                    }

                    if (isPaused) {
                        onProcessPaused(i, j, k);
                        return;
                    }

                    dataList.at(k)->start(i, j);
                    view->onErrorValueChanged(dataList.at(k)->getDelta());
                }

                updateSinaps();
            }
        }
    }

    view->onTrainingFinished();

    clearProcessParameters();
}

void MainInteractor::updateSinaps() {
    for (auto sinaps : sinapsList)
        sinaps->updateSinaps(0.7, 0);
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
    newData->setRepository(repository);
    newData->setPosition(x, y);

    neuronsList.push_back(newData);
    dataList.push_back(newData);
    view->onNewDataAdded(newData);
}

void MainInteractor::createNewPerceptron(PerceptronModel model) {
    PerceptronInteractor *newPerceptron = new PerceptronInteractor();

    newPerceptron->setInteractor(this);

    if (model.getID() > createdItemsCounter)
        createdItemsCounter = model.getID();

    neuronsList.push_back(newPerceptron);

    newPerceptron->updateFromModel(model);
    view->onNewPerceptronAdded(newPerceptron);
}

void MainInteractor::createNewData(DataModel model) {
    DataInteractor *newData = new DataInteractor();

    newData->setInteractor(this);
    newData->setRepository(repository);

    if (model.getID() > createdItemsCounter)
        createdItemsCounter = model.getID();

    neuronsList.push_back(newData);
    dataList.push_back(newData);

    newData->updateFromModel(model);
    view->onNewDataAdded(newData);
}

void MainInteractor::onDataModelLoaded(DataModel model) {
    createNewData(model);
}

void MainInteractor::onPerceptronModelLoaded(PerceptronModel model) {
    createNewPerceptron(model);
}

void MainInteractor::makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID) {
    if (dynamic_cast<PerceptronInteractor *>(findNeuron(learningNeuronID)) != nullptr)
        createNewWeight(learningNeuronID, dataNeuronID);
    else
        createNewCore(learningNeuronID, dataNeuronID);
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

void MainInteractor::onWeightModelLoaded(WeightModel model) {
    NeuronInteractor *inputNeuron = findNeuron(model.getInputNeuronID());
    NeuronInteractor *outputNeuron = findNeuron(model.getOutputNeuronID());

    WeightInteractor *newWeight = new WeightInteractor(inputNeuron, outputNeuron);

    if (inputNeuron->addArrow(newWeight) && outputNeuron->addArrow(newWeight)) {
        sinapsList.push_back(newWeight);
        newWeight->setInteractor(this);
        newWeight->setID(model.getID());
        newWeight->setWeight(model.getWeight());

        if (createdItemsCounter < model.getID())
            createdItemsCounter = model.getID();

        view->onNewWeightAdded(newWeight, model.getInputNeuronID(), model.getOutputNeuronID());
    }
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

std::vector<unsigned long> MainInteractor::getOutputsNeuronsList() {
    std::vector<unsigned long> outputsNeuronsList;

    for (auto neuron : neuronsList)
        if (neuron->isOutputNeuron())
            outputsNeuronsList.push_back(neuron->getID());

    return outputsNeuronsList;
}

void MainInteractor::stop() {
    isStopped = true;
}

void MainInteractor::pause() {
    isPaused = true;
}

void MainInteractor::debugRun() {
    isDebug = true;
}

void MainInteractor::save(std::string path) {
    std::vector<DataModel> dataModelList;
    std::vector<PerceptronModel> perceptronModelList;
    std::vector<WeightModel> weightModelList;

    for (auto neuron : neuronsList) {
        if (neuron->getType() == Perceptron)
            perceptronModelList.push_back(static_cast<PerceptronInteractor *>(neuron)->getModel());

        if (neuron->getType() == Data)
            dataModelList.push_back(static_cast<DataInteractor *>(neuron)->getModel());
    }

    for (auto sinaps : sinapsList) {
        if (sinaps->getType() == sinaps->Weigth && sinaps->getOutputNeuron()->getType() != Data)
            weightModelList.push_back(static_cast<WeightInteractor *>(sinaps)->getModel());
    }

    repository->save(path, dataModelList, perceptronModelList, weightModelList);
}

void MainInteractor::load(std::string path) {
    repository->load(path);
}

void MainInteractor::onProcessStopped() {
    for (auto neuron : neuronsList)
        neuron->clean();

    clearProcessParameters();
}

void MainInteractor::onProcessPaused(unsigned long pausedClassNumber, unsigned long pausedIterationNumber, unsigned long pausedNeuronNumber) {
    isPaused = false;
    this->pausedClassNumber = pausedClassNumber;
    this->pausedIterationNumber = pausedIterationNumber;
    this->pausedNeuronNumber = pausedNeuronNumber;
}

void MainInteractor::clearProcessParameters() {
    isStopped = false;
    isPaused = false;
    isDebug = false;
    pausedClassNumber = 0;
    pausedIterationNumber = 0;
    pausedNeuronNumber = 0;
}

NeuronInteractor *MainInteractor::findNeuron(unsigned long id) {
    for (auto neuron : neuronsList)
        if (neuron->getID() == id)
            return neuron;
    return nullptr;
}

MainInteractor * MainInteractor::instance;
