#ifndef SINAPSMODEL_H
#define SINAPSMODEL_H

#include <listeners/SinapsListener.h>

class SinapsModel
{
public:
    enum SinapsType {Weigth, Core};

public:
    SinapsModel(SinapsListener *inputListener, SinapsListener *outputListener);
    void setType(SinapsType type);
    void init();

private:
    void initWeight();
    void initCore();
    void clearValue();

private:
    SinapsListener *inputListener;
    SinapsListener *outputListener;
    SinapsType type;
    double *value = nullptr;
};

#endif // SINAPSMODEL_H
