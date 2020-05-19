#ifndef DATAINTERACTOR_H
#define DATAINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/datainteractorlistener.h"
#include "interfaces/datainteractorinterface.h"

class DataPresentorListener;
class RepositoryInterface;
class DataModel;

class DataInteractor : public NeuronInteractor, public DataInteractorListener, public DataInteractorInterface
{
public:
    DataInteractor();
    void start(unsigned long classNumber, unsigned long iterationNumber, bool isTraining) override;
    void setRepository(RepositoryInterface *repository);
    unsigned long getClassNumber() override;
    unsigned long getTrainingIterationNumber() override;
    unsigned long getTestingIterationNumber() override;
    void setPosition(double x, double y) override;
    double getLoss() override;
    double getAccuracy();
    DataModel getModel();
    void updateFromModel(DataModel model);
    unsigned int getAnswer() override;

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
    void setLossFunctionType(LossFunctionType type) override;
    void setColorModeEnable(bool enable) override;
    void setActivateFunctionType(int type) override;
    LossFunctionType getLossFunctionType() override;
    bool getColorModeEnable() override;
    int getActivateFunctiontype() override;
    void sendDelta();
    void calculateDelta();
    void calculateInputSignal();
    void calculateLoss();
    unsigned int getMaxIndex(std::vector<double> value);

private:
    DataPresentorListener *view;
    RepositoryInterface *repository;
    std::vector<std::vector<double>> value;
    std::vector<std::vector<std::vector<double>>> colorValue;
    std::vector<double> inputSignal;
    std::vector<double> currentDelta;
    std::vector<double> currentMark;
    unsigned long currentClass;
    double currentLoss;
    //Need to save
    bool isColorMode, isTraining;
    std::vector<ClassModel> classList;
    LossFunctionType lossFunctionType;
};

#endif // DATAINTERACTOR_H
