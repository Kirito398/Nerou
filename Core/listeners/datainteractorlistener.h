#ifndef DATAINTERACTORLISTENER_H
#define DATAINTERACTORLISTENER_H

class DataPresentorListener;

class DataInteractorListener
{
public:
    virtual void setView(DataPresentorListener *listener) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void deleteNeuron() = 0;
    virtual unsigned long getID() = 0;
};

#endif // DATAINTERACTORLISTENER_H
