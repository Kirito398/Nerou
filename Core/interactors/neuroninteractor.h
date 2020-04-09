#ifndef NEURONINTERACTOR_H
#define NEURONINTERACTOR_H

#include <vector>

#include "listeners/SinapsListener.h"

class SinapsInteractor;
class MainInteractorInterface;

class NeuronInteractor : public SinapsListener
{

public:
    NeuronInteractor(NeuronType type);
    virtual ~NeuronInteractor();
    virtual void clean() = 0;
    void setID(unsigned long id);
    unsigned long getID() override;
    bool addArrow(SinapsInteractor* arrow);
    void setInteractor(MainInteractorInterface *interface);
    bool isOutputNeuron();
    NeuronType getType() override;

protected:
    virtual void removeSinaps(unsigned long sinapsID) override;
    double activateFunction(double value);
    void activateFunction(double* value, unsigned int size);
    void activateFunction(double** value, unsigned int row, unsigned int column);
    double reActivateFunction(double value);
    double normalization(double value, double max, double min);
    std::vector<std::vector<double>> normalization(std::vector<std::vector<double>> value);
    std::vector<std::vector<std::vector<double>>> normalization(std::vector<std::vector<std::vector<double>>> value);
    double lossFunction(double answer, double idealAnswer);
    void makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID);
    void removeNeuron();
    void isOutputNeuronEnable(bool enable);
    std::vector<double> softmaxFunction(std::vector<double> values);
    double reSoftmaxFunction(double value);

private:
    virtual void onNeuronValueChanged(double newValue) override = 0;
    bool isArrowAlreadyAdded(SinapsInteractor* arrow);
    void removeSinapses();
    double sigmoidFunction(double value);
    double tanhFunction(double value);
    double reluFunction(double value);
    double reSigmoidFunction(double value);
    double reTanhFunction(double value);
    double reReluFunction(double value);
    double mseFunction(double answer, double idealAnswer);
    double crossEntropyFunction(double answer, double idealAnswer);

protected:
    unsigned long inputSignalCount;
    unsigned long inputDeltaCount;
    std::vector<SinapsInteractor *> inputsSinaps;
    std::vector<SinapsInteractor *> outputsSinaps;
    double posX, posY;
    unsigned long id;
    bool isOutput;
    NeuronType type;

private:
    MainInteractorInterface *interactor;
};

#endif // NEURONINTERACTOR_H
