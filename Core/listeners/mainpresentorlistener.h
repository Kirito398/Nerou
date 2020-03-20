#ifndef MAINPRESENTORLISTENER_H
#define MAINPRESENTORLISTENER_H

class PerceptronInteractorListener;
class DataInteractorListener;

class MainPresentorListener
{
public:
    virtual void onNewPerceptronAdded(PerceptronInteractorListener *perceptron) = 0;
    virtual void onNewDataAdded(DataInteractorListener *data) = 0;
    virtual void onTrainingStarted(unsigned int iterationCount, unsigned int epohCount) = 0;
    virtual void onEpohChanged(unsigned int currentEpoh) = 0;
    virtual void onIterationChanged(unsigned int currentIteration) = 0;
    virtual void onTrainingFinished() = 0;
    virtual void onErrorValueChanged(double value) = 0;
};

#endif // MAINPRESENTORLISTENER_H
