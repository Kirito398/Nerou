#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include <vector>
#include <string>

#include "interfaces/maininteractorinterface.h"

class NeuronInteractor;
class SinapsInteractor;
class DataInteractor;
class DataInteractorInterface;
class PerceptronInteractor;
class CoreInteractor;
class WeightInteractor;
class MainPresentorListener;
class ArrowInteractorListener;
class RepositoryInterface;
class DataModel;
class PerceptronModel;
class ConvolutionModel;

class MainInteractor : public MainInteractorInterface
{
public:
    static MainInteractor *getInstance(RepositoryInterface *repository);
    void setView(MainPresentorListener *listener);
    void createNewPerceptron(double x, double y);
    void createNewData(double x, double y);
    void createNewConvolution(double x, double y);
    void createNewTableData(double x, double y);
    ArrowInteractorListener *createNewWeight(unsigned long inputID, unsigned long outputID);
    ArrowInteractorListener *createNewCore(unsigned long inputID, unsigned long outputID);
    void removeNeuron(unsigned long neuronID) override;
    void removeSinaps(unsigned long sinapsID) override;
    std::vector<unsigned long> getOutputsNeuronsList();
    unsigned long getEpohNumber();
    void setEpohNumber(unsigned long value);
    double getLearningRange();
    void setLearningRange(double value);
    double getAlpha();
    void setAlpha(double value);
    std::string getCurrentProjectName();
    void setAnimateTrainingProcessEnable(bool enable);
    bool getAnimateTrainingProcessEnable();

    void save(std::string path);
    void load(std::string path);
    void run();
    void stop();
    void pause();
    void debugRun();

private:
    MainInteractor(RepositoryInterface *repository);
    void createNewPerceptron(PerceptronModel model);
    void createNewData(DataModel model);
    void createNewTableData(TableDataModel model);
    void createNewConvolution(ConvolutionModel model);
    NeuronInteractor *findNeuron(unsigned long id);
    void onProcessStopped();
    void onProcessPaused(unsigned long pausedClassNumber, unsigned long pausedIterationNumber, unsigned long pausedNeuronNumber);
    void clearProcessParameters();
    void updateSinaps();
    void makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID) override;
    void onDataModelLoaded(DataModel model) override;
    void onPerceptronModelLoaded(PerceptronModel model) override;
    void onConvolutionModelLoaded(ConvolutionModel model) override;
    void onWeightModelLoaded(WeightModel model) override;
    void onCoreModelLoaded(CoreModel model) override;
    void onTableDataModelLoaded(TableDataModel model) override;
    void train(unsigned long classNumber, unsigned long iterationNumber, unsigned long neuronNumber);
    void testing(unsigned long classNumber, unsigned long iterationNumber, unsigned long neuronNumber);
    double calculateLearningRangeDecay(double learningRange0);

private:
    static MainInteractor *instance;
    MainPresentorListener *view;
    RepositoryInterface *repository;
    std::vector<NeuronInteractor *> neuronsList;
    std::vector<SinapsInteractor *> sinapsList;
    std::vector<DataInteractorInterface *> dataList;
    unsigned long createdItemsCounter;
    bool isStopped, isPaused, isDebug;
    unsigned long pausedClassNumber, pausedIterationNumber, pausedNeuronNumber;
    unsigned long epohNumber;
    double learningRange, alpha, learningRangeDecay;
    unsigned long learningRangeDecayCounter;
    std::string currentProjectName;
    bool isTrainingProcessAnimated;
};

#endif // MAININTERACTOR_H
