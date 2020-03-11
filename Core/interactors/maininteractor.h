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

class MainInteractor : public MainInteractorInterface
{
public:
    static MainInteractor *getInstance();
    void setView(MainPresentorListener *listener);
    void createNewPerceptron(double x, double y);
    void createNewData(double x, double y);
    ArrowInteractorListener *createNewWeight(unsigned long inputID, unsigned long outputID);
    ArrowInteractorListener *createNewCore(unsigned long inputID, unsigned long outputID);
    void removeNeuron(unsigned long neuronID) override;
    void removeSinaps(unsigned long sinapsID) override;
    void run();

private:
    NeuronInteractor *findNeuron(unsigned long id);

private:
    MainInteractor();
    static MainInteractor *instance;
    std::vector<NeuronInteractor *> neuronsList;
    std::vector<SinapsInteractor *> sinapsList;
    std::vector<DataInteractor *> dataList;
    MainPresentorListener *view;
    unsigned long createdItemsCounter;
};

#endif // MAININTERACTOR_H
