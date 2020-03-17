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
    virtual void addClass(std::vector<std::string> pathList, unsigned long neuronID, bool isTrainingSet) = 0;
    virtual unsigned long getID() = 0;
    virtual void setSize(unsigned long row, unsigned long column) = 0;
    virtual void clearPathsList() = 0;
};

#endif // DATAINTERACTORLISTENER_H
