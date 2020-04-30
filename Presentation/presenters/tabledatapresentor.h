#ifndef TABLEDATAPRESENTOR_H
#define TABLEDATAPRESENTOR_H

#include "listeners/tabledatapresentorlistener.h"
#include "listeners/tabledatainteractorlistener.h"

class TableDataViewListener;

class TableDataPresentor : public TableDataPresentorListener
{
public:
    TableDataPresentor();
    ~TableDataPresentor();
    void setView(TableDataViewListener *listener);
    void setInteractor(TableDataInteractorListener *listener);
    void setPosition(double x, double y);
    unsigned long getID();
    void setActivateFunctionType(int type);
    int getActivateFunctionType();
    void setLossFunctionType(LossFunctionType type);
    LossFunctionType getLossFunctionType();

private:
    void updatePosition(double x, double y) override;

private:
    TableDataViewListener *view;
    TableDataInteractorListener *interactor;
};

#endif // TABLEDATAPRESENTOR_H
