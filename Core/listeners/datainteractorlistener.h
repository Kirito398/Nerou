#ifndef DATAINTERACTORLISTENER_H
#define DATAINTERACTORLISTENER_H

#include <string>
#include <vector>

class DataPresentorListener;

class DataInteractorListener
{
public:
    virtual void setView(DataPresentorListener *listener) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void deleteNeuron() = 0;
    virtual void addClass(std::vector<std::string> list) = 0;
    virtual unsigned long getID() = 0;
};

#endif // DATAINTERACTORLISTENER_H
