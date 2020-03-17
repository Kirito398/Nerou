#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include <vector>

#include "interfaces/maininteractorinterface.h"

class NeuronInteractor;
class SinapsInteractor;
class DataInteractor;
class PerceptronInteractor;
class CoreInteractor;
class WeightInteractor;
class MainPresentorListener;
class ArrowInteractorListener;
class RepositoryInterface;

class MainInteractor : public MainInteractorInterface
{
public:
    static MainInteractor *getInstance(RepositoryInterface *repository);
    void setView(MainPresentorListener *listener);
    void createNewPerceptron(double x, double y);
    void createNewData(double x, double y);
    ArrowInteractorListener *createNewWeight(unsigned long inputID, unsigned long outputID);
    ArrowInteractorListener *createNewCore(unsigned long inputID, unsigned long outputID);
    void removeNeuron(unsigned long neuronID) override;
    void removeSinaps(unsigned long sinapsID) override;
    void run();
    void stop();
    void pause();
    void debugRun();

private:
    MainInteractor(RepositoryInterface *repository);
    NeuronInteractor *findNeuron(unsigned long id);
    void onProcessStopped();
    void onProcessPaused(unsigned long pausedClassNumber, unsigned long pausedIterationNumber, unsigned long pausedNeuronNumber);
    void clearProcessParameters();
    void makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID) override;

private:
    static MainInteractor *instance;
    MainPresentorListener *view;
    RepositoryInterface *repository;
    std::vector<NeuronInteractor *> neuronsList;
    std::vector<SinapsInteractor *> sinapsList;
    std::vector<DataInteractor *> dataList;
    unsigned long createdItemsCounter;
    bool isStopped, isPaused, isDebug;
    unsigned long pausedClassNumber, pausedIterationNumber, pausedNeuronNumber;
};

#endif // MAININTERACTOR_H
