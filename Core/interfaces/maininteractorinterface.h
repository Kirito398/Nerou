#ifndef MAININTERACTORINTERFACE_H
#define MAININTERACTORINTERFACE_H

class ArrowInteractorListener;
class DataModel;
class PerceptronModel;
class WeightModel;
class ConvolutionModel;
class CoreModel;

enum ActivateFunctionType {Linear, Sigmoid, Tanh, ReLU};
enum LossFunctionType {MSE, CrossEntropy};

class MainInteractorInterface
{
public:
    virtual void removeSinaps(unsigned long sinapsID) = 0;
    virtual void removeNeuron(unsigned long neuronID) = 0;
    virtual void makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID) = 0;
    virtual void onDataModelLoaded(DataModel model) = 0;
    virtual void onPerceptronModelLoaded(PerceptronModel model) = 0;
    virtual void onConvolutionModelLoaded(ConvolutionModel model) = 0;
    virtual void onWeightModelLoaded(WeightModel model) = 0;
    virtual void onCoreModelLoaded(CoreModel model) = 0;
    virtual ActivateFunctionType getActivateFunctionType() = 0;
    virtual LossFunctionType getLossFunctionType() = 0;
};

#endif // MAININTERACTORINTERFACE_H
