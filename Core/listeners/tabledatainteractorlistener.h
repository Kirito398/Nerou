#ifndef TABLEDATAINTERACTORLISTENER_H
#define TABLEDATAINTERACTORLISTENER_H

#include "enums/lossfunctiontypeenum.h"

class TableDataModel;
class TableDataPresentorListener;
class RepositoryInterface;

class TableDataInteractorListener
{
public:
    virtual void setView(TableDataPresentorListener *listener) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void deleteNeuron() = 0;
    virtual unsigned long getID() = 0;
    virtual void setLossFunctionType(LossFunctionType type) = 0;
    virtual LossFunctionType getLossFunctionType() = 0;
    virtual void setActivateFunctionType(int type) = 0;
    virtual int getActivateFunctiontype() = 0;
};

#endif // TABLEDATAINTERACTORLISTENER_H
