#ifndef NEURONINTERACTOR_H
#define NEURONINTERACTOR_H

#include <vector>

#include "listeners/SinapsListener.h"

class SinapsInteractor;
class MainInteractorInterface;

class NeuronInteractor : public SinapsListener
{
public:
    enum ActivateFunctionType {Sigmoid, Tanh, ReLU, Softmax};

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
    void setAnimateTrainingProcessEnable(bool enable);

protected:
    virtual void removeSinaps(unsigned long sinapsID) override;
    double activateFunction(double value);
    void activateFunction(double* value, unsigned int size);
    void activateFunction(double** value, unsigned int row, unsigned int column);
    double reActivateFunction(double value);
    double normalization(double value, double max, double min);
    std::vector<std::vector<double>> normalization(std::vector<std::vector<double>> value);
    std::vector<std::vector<std::vector<double>>> normalization(std::vector<std::vector<std::vector<double>>> value);
    void makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID);
    void removeNeuron();
    void isOutputNeuronEnable(bool enable);
    std::vector<double> softmaxFunction(std::vector<double> values);
    double reSoftmaxFunction(double value);
    double mseFunction(std::vector<double> answer, std::vector<double> mark);
    double crossEntropyFunction(std::vector<double> answer, std::vector<double> mark);

private:
    bool isArrowAlreadyAdded(SinapsInteractor* arrow);
    void removeSinapses();
    double sigmoidFunction(double value);
    double tanhFunction(double value);
    double reluFunction(double value);
    double reSigmoidFunction(double value);
    double reTanhFunction(double value);
    double reReluFunction(double value);
    unsigned long getInputSignalSize() override;
    unsigned long getOutputSignalSize() override;

protected:
    unsigned long inputSignalCount;
    unsigned long inputDeltaCount;
    std::vector<SinapsInteractor *> inputsSinaps;
    std::vector<SinapsInteractor *> outputsSinaps;
    double posX, posY;
    unsigned long id;
    bool isOutput, isAnimateTrainingProcessEnabled;
    NeuronType type;
    ActivateFunctionType activateFunctionType;

private:
    MainInteractorInterface *interactor;
};

#endif // NEURONINTERACTOR_H
