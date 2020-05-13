#ifndef PERCEPTRONINTERACTORLISTENER_H
#define PERCEPTRONINTERACTORLISTENER_H

class PerceptronPresentorListener;

class PerceptronInteractorListener
{
public:
    virtual void setView(PerceptronPresentorListener *listener) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void deleteNeuron() = 0;
    virtual unsigned long getID() = 0;
    virtual void setOutputNeuron(bool enable) = 0;
    virtual bool getIsOutputNeuron() = 0;
    virtual void setActivateFunctionType(int type) = 0;
    virtual int getActivateFunctionType() = 0;
};

#endif // PERCEPTRONINTERACTORLISTENER_H
