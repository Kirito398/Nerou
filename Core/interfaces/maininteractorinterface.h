#ifndef MAININTERACTORINTERFACE_H
#define MAININTERACTORINTERFACE_H


class MainInteractorInterface
{
public:
    virtual void removeSinaps(unsigned long sinapsID) = 0;
    virtual void removeNeuron(unsigned long neuronID) = 0;
};

#endif // MAININTERACTORINTERFACE_H
