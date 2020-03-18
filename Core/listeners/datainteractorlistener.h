#ifndef DATAINTERACTORLISTENER_H
#define DATAINTERACTORLISTENER_H

class ClassModel;

class DataPresentorListener;

class DataInteractorListener
{
public:
    virtual void setView(DataPresentorListener *listener) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void deleteNeuron() = 0;
    virtual void addClass(ClassModel model) = 0;
    virtual unsigned long getID() = 0;
    virtual void setSize(unsigned long row, unsigned long column) = 0;
    virtual void clearClassList() = 0;
    virtual unsigned long getClassNumber() = 0;
    virtual ClassModel getClass(unsigned long id) = 0;
};

#endif // DATAINTERACTORLISTENER_H
