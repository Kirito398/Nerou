#ifndef MAININTERACTORINTERFACE_H
#define MAININTERACTORINTERFACE_H

class ArrowInteractorListener;
class DataModel;
class PerceptronModel;
class WeightModel;

class MainInteractorInterface
{
public:
    virtual void removeSinaps(unsigned long sinapsID) = 0;
    virtual void removeNeuron(unsigned long neuronID) = 0;
    virtual void makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID) = 0;
    virtual void onDataModelLoaded(DataModel model) = 0;
    virtual void onPerceptronModelLoaded(PerceptronModel model) = 0;
    virtual void onWeightModelLoaded(WeightModel model) = 0;
};

#endif // MAININTERACTORINTERFACE_H
