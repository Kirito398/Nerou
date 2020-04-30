#ifndef MAINPRESENTORLISTENER_H
#define MAINPRESENTORLISTENER_H

#include <string>

class PerceptronInteractorListener;
class DataInteractorListener;
class ArrowInteractorListener;
class ConvolutionInteractorListener;
class TableDataInteractorListener;

class MainPresentorListener
{
public:
    virtual void onNewPerceptronAdded(PerceptronInteractorListener *perceptron) = 0;
    virtual void onNewDataAdded(DataInteractorListener *data) = 0;
    virtual void onNewWeightAdded(ArrowInteractorListener *arrow, unsigned long startNeuronID, unsigned long endNeuronID) = 0;
    virtual void onNewCoreAdded(ArrowInteractorListener *arrow, unsigned long startNeuronID, unsigned long endNeuronID) = 0;
    virtual void onNewConvolutionAdded(ConvolutionInteractorListener *convolution) = 0;
    virtual void onNewTableDataAdded(TableDataInteractorListener *tableData) = 0;
    virtual void onTrainingStarted(unsigned int iterationCount, unsigned int epohCount) = 0;
    virtual void onEpohChanged(unsigned int currentEpoh) = 0;
    virtual void onIterationChanged(unsigned int currentIteration) = 0;
    virtual void onTrainingFinished() = 0;
    virtual void onErrorValueChanged(double value) = 0;
    virtual void onAccuracyChanged(double value) = 0;
    virtual void onProjectNameChanged(std::string name) = 0;
};

#endif // MAINPRESENTORLISTENER_H
