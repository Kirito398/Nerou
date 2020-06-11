#ifndef SINAPSLISTENER_H
#define SINAPSLISTENER_H

enum NeuronType {Perceptron, Convolution, Data};

class SinapsListener
{
public:
    virtual void onInputSignalChanged() = 0;
    virtual void onDeltaValueChanged() = 0;
    virtual void removeSinaps(unsigned long sinapsID) = 0;
    virtual unsigned long getID() = 0;
    virtual NeuronType getType() = 0;
    virtual unsigned long getInputSignalSize() = 0;
    virtual unsigned long getOutputSignalSize() = 0;
};

#endif // SINAPSLISTENER_H
