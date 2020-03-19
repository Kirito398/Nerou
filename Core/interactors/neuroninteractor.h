#ifndef NEURONINTERACTOR_H
#define NEURONINTERACTOR_H

#include <vector>

#include "listeners/SinapsListener.h"

class SinapsInteractor;
class MainInteractorInterface;

class NeuronInteractor : public SinapsListener
{
public:
    enum FunctionType {Sin};

public:
    NeuronInteractor(NeuronType type);
    virtual ~NeuronInteractor();
    virtual void clean() = 0;
    void setID(unsigned long id);
    unsigned long getID() override;
    bool addArrow(SinapsInteractor* arrow);
    void setInteractor(MainInteractorInterface *interface);
    bool isOutputNeuron();

protected:
    virtual void removeSinaps(unsigned long sinapsID) override;
    double activateFunction(double value);
    void activateFunction(double* value, unsigned int size);
    void activateFunction(double** value, unsigned int row, unsigned int column);
    double normalization(double value, double max, double min);
    void normalization(double* value, unsigned int size);
    void normalization(double** value, unsigned int row, unsigned int column);
    void makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID);
    void removeNeuron();
    void isOutputNeuronEnable(bool enable);

private:
    bool isArrowAlreadyAdded(SinapsInteractor* arrow);
    void removeSinapses();
    NeuronType getType() override;

protected:
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
