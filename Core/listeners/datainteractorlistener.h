#ifndef DATAINTERACTORLISTENER_H
#define DATAINTERACTORLISTENER_H

#include "enums/lossfunctiontypeenum.h"

class ClassModel;
class DataPresentorListener;
class RepositoryInterface;

class DataInteractorListener
{
public:
    virtual void setView(DataPresentorListener *listener) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void deleteNeuron() = 0;
    virtual void addClass(ClassModel model) = 0;
    virtual unsigned long getID() = 0;
    virtual void clearClassList() = 0;
    virtual unsigned long getClassNumber() = 0;
    virtual ClassModel getClass(unsigned long id) = 0;
    virtual RepositoryInterface *getRepository() = 0;
    virtual void setColorModeEnable(bool enable) = 0;
    virtual bool getColorModeEnable() = 0;
    virtual void setLossFunctionType(LossFunctionType type) = 0;
    virtual LossFunctionType getLossFunctionType() = 0;
    virtual void setActivateFunctionType(int type) = 0;
    virtual int getActivateFunctiontype() = 0;
};

#endif // DATAINTERACTORLISTENER_H
