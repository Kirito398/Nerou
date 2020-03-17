#ifndef DATAINTERACTOR_H
#define DATAINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/datainteractorlistener.h"

class DataPresentorListener;
class RepositoryInterface;

class DataInteractor : public NeuronInteractor, public DataInteractorListener
{
public:
    DataInteractor();
    void start(unsigned long classNumber, unsigned long iterationNumber);
    void setRepository(RepositoryInterface *repository);
    unsigned long getClassNumber();
    unsigned long getIterationNumber();
    void setPosition(double x, double y) override;

private:
    void sendData();
    void colorsToValue();
    void clearColorValue();
    void clearValue();
    unsigned long getID() override;
    void deleteNeuron() override;
    void addClass(std::vector<std::string> pathList, unsigned long neuronID, bool isTrainingSet) override;
    void onInputSignalChanged() override;
    void onDeltaValueChanged() override;
    void setView(DataPresentorListener *listener) override;
    void setSize(unsigned long row, unsigned long column) override;
    void clean() override;
    void clearPathsList() override;

private:
    DataPresentorListener *view;
    RepositoryInterface *repository;
    bool isColorMode;
    double *value, **colorValue;
    unsigned int row, column;
    unsigned long trainingClassNumber, trainingIterationNumber;
    std::vector<std::vector<std::string>> trainingListPaths;
    std::vector<unsigned long> trainingNeuronsID;
};

#endif // DATAINTERACTOR_H
