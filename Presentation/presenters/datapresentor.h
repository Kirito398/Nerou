#ifndef DATAPRESENTOR_H
#define DATAPRESENTOR_H

#include "listeners/datapresentorlistener.h"

class QPointF;
class DataViewListener;
class DataInteractorListener;

class DataPresentor : public DataPresentorListener
{
public:
    DataPresentor();
    void setView(DataViewListener *listener);
    void setInteractor(DataInteractorListener *listener);
    void setPosition(double x, double y);
    unsigned long getID();

private:
    void updatePosition(double x, double y) override;

private:
    DataViewListener *view;
    DataInteractorListener *interactor;
};

#endif // DATAPRESENTOR_H
