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
    void addClass(std::vector<std::string> list) override;
    void onInputSignalChanged() override;
    void onDeltaValueChanged() override;
    void setView(DataPresentorListener *listener) override;
    void setSize(unsigned long row, unsigned long column) override;

private:
    DataPresentorListener *view;
    RepositoryInterface *repository;
    bool isColorMode;
    double *value, **colorValue;
    unsigned int row, column;
    unsigned long classNumber, iterationNumber;
    std::vector<std::vector<std::string>> listPaths;
};

#endif // DATAINTERACTOR_H
