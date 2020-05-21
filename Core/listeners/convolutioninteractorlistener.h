#ifndef CONVOLUTIONINTERACTORLISTENER_H
#define CONVOLUTIONINTERACTORLISTENER_H

class ConvolutionPresentorListener;

class ConvolutionInteractorListener
{
public:
    virtual void setView(ConvolutionPresentorListener *listener) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void deleteNeuron() = 0;
    virtual unsigned long getID() = 0;
    virtual int getActivateFunctionType() = 0;
    virtual void setActivateFunctionType(int type) = 0;
    virtual void setCoreSize(int size) = 0;
    virtual int getCoreSize() = 0;
    virtual void setPoolCoreSize(int size) = 0;
    virtual int getPoolCoreSize() = 0;
};

#endif // CONVOLUTIONINTERACTORLISTENER_H
