#ifndef TABLEDATAINTERACTOR_H
#define TABLEDATAINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/tabledatainteractorlistener.h"
#include "interfaces/datainteractorinterface.h"

class TableDataSetModel;
class TableDataModel;

class TableDataInteractor : public NeuronInteractor, public TableDataInteractorListener, public DataInteractorInterface
{
public:
    TableDataInteractor();
    void setPosition(double x, double y) override;
    void setRepository(RepositoryInterface *repository);
    TableDataModel getModel();
    void updateFromModel(TableDataModel model);

private:
    void removeSinaps(unsigned long sinapsID) override;
    void clean() override;
    void setView(TableDataPresentorListener *listener) override;
    void deleteNeuron() override;
    unsigned long getID() override;
    void setLossFunctionType(LossFunctionType type) override;
    LossFunctionType getLossFunctionType() override;
    void setActivateFunctionType(int type) override;
    int getActivateFunctiontype() override;
    void onInputSignalChanged() override;
    void onDeltaValueChanged() override;
    std::vector<std::vector<std::string> > loadTableValue(std::string path) override;
    std::string getDataSetMainPath() override;
    void setDataSetMainPath(std::string path) override;
    void addTestingInputSet(std::vector<double> set) override;
    void addTestingTargetSet(std::vector<double> set) override;
    void addTrainingInputSet(std::vector<double> set) override;
    void addTrainingTargetSet(std::vector<double> set) override;
    void setInputsTitles(std::vector<std::string> titles) override;
    void setTargetTitles(std::vector<std::string> titles, std::vector<unsigned long> outputsNeuronsID) override;
    std::vector<std::string> getInputsTitles() override;
    std::vector<std::string> getTargetTitles() override;
    void clearDataSet() override;
    unsigned long getClassNumber() override;
    unsigned long getTrainingIterationNumber() override;
    void start(unsigned long classNumber, unsigned long iterationNumber) override;
    double getLoss() override;
    unsigned int getAnswer() override;
    size_t getOutputNeuronsNumber() override;
    std::vector<double> makeNormalize(std::vector<double> value, std::vector<double> max, std::vector<double> min);
    void calculateInputSignal();
    void calculateLoss();
    void calculateDelta();
    void sendDelta();

private:
    TableDataPresentorListener *view;
    RepositoryInterface *repository;
    LossFunctionType lossFunctionType;
    TableDataSetModel *dataSet;
    unsigned long currentAnswer;
    std::vector<double> inputSignal;
    std::vector<double> currentMark;
    std::vector<double> currentDelta;
    double currentLoss;
    double epsilon;
};

#endif // TABLEDATAINTERACTOR_H
