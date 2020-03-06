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
    void run();

private:
    MainInteractor();
    static MainInteractor *instance;
    std::vector<NeuronInteractor *> neuronsList;
    std::vector<SinapsInteractor *> sinapsList;
    MainPresentorListener *view;
};

#endif // MAININTERACTOR_H
