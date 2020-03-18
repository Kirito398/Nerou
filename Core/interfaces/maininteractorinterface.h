#ifndef MAININTERACTORINTERFACE_H
#define MAININTERACTORINTERFACE_H

class ArrowInteractorListener;

class MainInteractorInterface
{
public:
    virtual void removeSinaps(unsigned long sinapsID) = 0;
    virtual void removeNeuron(unsigned long neuronID) = 0;
    virtual void makeLearningSinaps(unsigned long learningNeuronID, unsigned long dataNeuronID) = 0;
};

#endif // MAININTERACTORINTERFACE_H
