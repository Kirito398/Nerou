#ifndef SINAPSMODEL_H
#define SINAPSMODEL_H

#include "listeners/SinapsListener.h"

class SinapsModel
{
public:
    enum SinapsType {Weigth, Core};

public:
    SinapsModel(SinapsListener *inputListener, SinapsListener *outputListener, SinapsType type);
    virtual void init() = 0;
    virtual ~SinapsModel();

protected:
    double random();

protected:
    SinapsListener *inputListener;
    SinapsListener *outputListener;

private:
    SinapsType type;
};

#endif // SINAPSMODEL_H
