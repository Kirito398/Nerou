#ifndef DATAINTERACTOR_H
#define DATAINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/datainteractorlistener.h"

class DataPresentorListener;

class DataInteractor : public NeuronInteractor, public DataInteractorListener
{
public:
    DataInteractor();
    void onInputSignalChanged() override;
    void sendData();
};

#endif // DATAINTERACTOR_H
