#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include <vector>

class NeuronInteractor;
class SinapsInteractor;
class DataInteractor;
class PerceptronInteractor;
class CoreInteractor;
class WeightInteractor;
class MainPresentorListener;

class MainInteractor
{
public:
    static MainInteractor *getInstance();
    void setView(MainPresentorListener *listener);
    void createNewPerceptron();
    void createNewData();
    void createNewWeight(unsigned long inputID, unsigned long outputID);
    void createNewCore(unsigned long inputID, unsigned long outputID);
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
    unsigned long createdNeuronCount;
};

#endif // MAININTERACTOR_H
