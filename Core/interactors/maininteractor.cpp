#include "maininteractor.h"

#include "interactors/neuroninteractor.h"
#include "interactors/sinapsinteractor.h"
#include "interactors/datainteractor.h"
#include "interactors/perceptroninteractor.h"
#include "interactors/weightinteractor.h"
#include "interactors/coreinteractor.h"
#include "interactors/convolutioninteractor.h"
#include "interactors/tabledatainteractor.h"
#include "listeners/mainpresentorlistener.h"
#include "interfaces/repositoryinterface.h"
#include "models/datamodel.h"
#include "models/perceptronmodel.h"
#include "models/classmodel.h"
#include "models/weightmodel.h"
#include "models/convolutionmodel.h"
#include "models/coremodel.h"
#include "models/tabledatamodel.h"

MainInteractor::MainInteractor(RepositoryInterface *repository)
{
    this->repository = repository;
    repository->setInteractor(this);
    createdItemsCounter = 0;
    epohNumber = 30;
    learningRange = 0.3;
    alpha = 0.0;
    currentProjectName = "Untitled";

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

    view->onTrainingStarted(iterationNumber, epohNumber);

    for (unsigned long e = 0; e < epohNumber; e++) {
        view->onEpohChanged(e + 1);
        double correctAnswerSum = 0.0;
        double answerCounter = 0.0;
        double totalLossValue = 0.0;
        int totalLossValueCounter = 0;

        for (unsigned long j = pausedIterationNumber; j < iterationNumber; j++) {
            view->onIterationChanged(j + 1);
            double lossSum = 0;

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
                    lossSum += dataList.at(k)->getLoss();

                    if (dataList.at(k)->getAnswer() == i)
                        correctAnswerSum++;
                    answerCounter++;
                }

                updateSinaps();
            }

            view->onAccuracyChanged(correctAnswerSum / answerCounter);
            view->onErrorValueChanged(lossSum / classNumber);
            totalLossValue += (lossSum / classNumber);
            totalLossValueCounter++;
        }

        view->onTotalLossValueChanged(totalLossValue / totalLossValueCounter);
    }

    view->onTrainingFinished();

    clearProcessParameters();
}

void MainInteractor::updateSinaps() {
    for (auto sinaps : sinapsList)
        sinaps->updateSinaps(learningRange, alpha);
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

void MainInteractor::createNewConvolution(double x, double y) {
    ConvolutionInteractor *newConvolution = new ConvolutionInteractor();

    newConvolution->setID(++createdItemsCounter);
    newConvolution->setInteractor(this);
    newConvolution->setPosition(x, y);

    neuronsList.push_back(newConvolution);
    view->onNewConvolutionAdded(newConvolution);
}

void MainInteractor::createNewTableData(double x, double y) {
    TableDataInteractor *newData = new TableDataInteractor();

    newData->setID(++createdItemsCounter);
    newData->setInteractor(this);
    newData->setRepository(repository);
    newData->setPosition(x, y);

    neuronsList.push_back(newData);
    dataList.push_back(newData);
    view->onNewTableDataAdded(newData);
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

void MainInteractor::createNewTableData(TableDataModel model) {
    TableDataInteractor *newData = new TableDataInteractor();

    newData->setInteractor(this);
    newData->setRepository(repository);

    if (model.getID() > createdItemsCounter)
        createdItemsCounter = model.getID();

    neuronsList.push_back(newData);
    dataList.push_back(newData);

    newData->updateFromModel(model);
    view->onNewTableDataAdded(newData);
}

void MainInteractor::createNewConvolution(ConvolutionModel model) {
    ConvolutionInteractor *newConvolution = new ConvolutionInteractor();

    newConvolution->setInteractor(this);

    if (model.getID() > createdItemsCounter)
        createdItemsCounter = model.getID();

    neuronsList.push_back(newConvolution);

    newConvolution->updateFromModel(model);
    view->onNewConvolutionAdded(newConvolution);
}

void MainInteractor::onDataModelLoaded(DataModel model) {
    createNewData(model);
}

void MainInteractor::onTableDataModelLoaded(TableDataModel model){
    createNewTableData(model);
}

void MainInteractor::onPerceptronModelLoaded(PerceptronModel model) {
    createNewPerceptron(model);
}

void MainInteractor::onConvolutionModelLoaded(ConvolutionModel model) {
    createNewConvolution(model);
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

void MainInteractor::onCoreModelLoaded(CoreModel model) {
    NeuronInteractor *inputNeuron = findNeuron(model.getInputNeuronID());
    NeuronInteractor *outputNeuron = findNeuron(model.getOutputNeuronID());

    CoreInteractor *newCore = new CoreInteractor(inputNeuron, outputNeuron);

    if (inputNeuron->addArrow(newCore) && outputNeuron->addArrow(newCore)) {
        sinapsList.push_back(newCore);
        newCore->setInteractor(this);
        newCore->setID(model.getID());
        newCore->updateFromModel(model);

        if (createdItemsCounter < model.getID())
            createdItemsCounter = model.getID();

        view->onNewCoreAdded(newCore, model.getInputNeuronID(), model.getOutputNeuronID());
    }
}

void MainInteractor::removeNeuron(unsigned long neuronID) {
    NeuronInteractor *neuron = nullptr;

//    for (unsigned long i = 0; i < dataList.size(); i++) {
//        neuron = dataList.at(i);

//        if (neuron->getID() == neuronID) {
//            dataList.erase(dataList.begin() + i);
//            std::vector<DataInteractor *>(dataList).swap(dataList);
//            neuron = nullptr;
//            break;
//        }
//    }

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

unsigned long MainInteractor::getEpohNumber() {
    return epohNumber;
}

void MainInteractor::setEpohNumber(unsigned long value) {
    epohNumber = value;
}

double MainInteractor::getLearningRange() {
    return learningRange;
}

void MainInteractor::setLearningRange(double value) {
    learningRange = value;
}

double MainInteractor::getAlpha() {
    return alpha;
}

void MainInteractor::setAlpha(double value) {
    alpha = value;
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
    std::vector<ConvolutionModel> convolutionModelList;
    std::vector<WeightModel> weightModelList;
    std::vector<CoreModel> coreModelList;
    std::vector<TableDataModel> tableDataModelList;

    for (auto neuron : neuronsList) {
        if (neuron->getType() == Perceptron)
            perceptronModelList.push_back(static_cast<PerceptronInteractor *>(neuron)->getModel());

        if (neuron->getType() == Convolution)
            convolutionModelList.push_back(static_cast<ConvolutionInteractor *>(neuron)->getModel());

        if (neuron->getType() == Data) {
            DataInteractor *data = dynamic_cast<DataInteractor *>(neuron);
            if (data != nullptr) {
                dataModelList.push_back(data->getModel());
                continue;
            }

            TableDataInteractor *tableData = dynamic_cast<TableDataInteractor *>(neuron);
            if (tableData != nullptr) {
                tableDataModelList.push_back(tableData->getModel());
                continue;
            }
        }
    }

    for (auto sinaps : sinapsList) {
        if (sinaps->getType() == sinaps->Weigth && sinaps->getOutputNeuron()->getType() != Data)
            weightModelList.push_back(static_cast<WeightInteractor *>(sinaps)->getModel());

        if (sinaps->getType() == sinaps->Core && sinaps->getOutputNeuron()->getType() != Data)
            coreModelList.push_back(static_cast<CoreInteractor *>(sinaps)->getModel());
    }

    repository->save(path, dataModelList, perceptronModelList, convolutionModelList, weightModelList, coreModelList, tableDataModelList);

    currentProjectName = path;
    view->onProjectNameChanged(currentProjectName);
}

void MainInteractor::load(std::string path) {
    repository->load(path);

    currentProjectName = path;
    view->onProjectNameChanged(currentProjectName);
}

void MainInteractor::onProcessStopped() {
    for (auto neuron : neuronsList)
        neuron->clean();

    clearProcessParameters();
    view->onTrainingFinished();
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

std::string MainInteractor::getCurrentProjectName() {
    return currentProjectName;
}

NeuronInteractor *MainInteractor::findNeuron(unsigned long id) {
    for (auto neuron : neuronsList)
        if (neuron->getID() == id)
            return neuron;
    return nullptr;
}

MainInteractor * MainInteractor::instance;
