#ifndef DATAINTERACTOR_H
#define DATAINTERACTOR_H

#include <string>

#include "interactors/neuroninteractor.h"
#include "listeners/datainteractorlistener.h"

class DataPresentorListener;
class RepositoryInterface;

class DataInteractor : public NeuronInteractor, public DataInteractorListener
{
public:
    DataInteractor();
    void onInputSignalChanged() override;
    void onDeltaValueChanged() override;
    void setView(DataPresentorListener *listener) override;

    void start(unsigned long classNumber, unsigned long iterationNumber);
    void setRepository(RepositoryInterface *repository);

private:
    void sendData();

private:
    DataPresentorListener *view;
    RepositoryInterface *repository;
    double *value;
    unsigned int row, column;
    unsigned long classCounter, iterationColunter;
    std::vector<std::vector<std::string>> listPaths;
};

#endif // DATAINTERACTOR_H
