#ifndef DATAINTERACTOR_H
#define DATAINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/datainteractorlistener.h"

class DataPresentorListener;
class RepositoryInterface;
class DataModel;

class DataInteractor : public NeuronInteractor, public DataInteractorListener
{
public:
    DataInteractor();
    void start(unsigned long classNumber, unsigned long iterationNumber);
    void setRepository(RepositoryInterface *repository);
    unsigned long getClassNumber() override;
    unsigned long getTrainingIterationNumber();
    void setPosition(double x, double y) override;
    double getDelta();
    DataModel getModel();
    void updateFromModel(DataModel model);

private:
    void sendData();
    double *colorsToValue();
    double *valueToLine();
    unsigned long getID() override;
    void deleteNeuron() override;
    void addClass(ClassModel model) override;
    void onInputSignalChanged() override;
    void onDeltaValueChanged() override;
    void setView(DataPresentorListener *listener) override;
    void clean() override;
    void clearClassList() override;
    ClassModel getClass(unsigned long id) override;
    RepositoryInterface *getRepository() override;
    void removeSinaps(unsigned long sinapsID) override;
    void sendDelta();
    void calculateDelta();

private:
    DataPresentorListener *view;
    RepositoryInterface *repository;
    std::vector<std::vector<double>> value;
    std::vector<std::vector<std::vector<double>>> colorValue;
    unsigned long currentClass;
    double currentDelta;
    //Need to save
    bool isColorMode;
    std::vector<ClassModel> classList;
};

#endif // DATAINTERACTOR_H
