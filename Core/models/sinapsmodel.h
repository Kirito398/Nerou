#ifndef SINAPSMODEL_H
#define SINAPSMODEL_H

#include <listeners/SinapsListener.h>


class SinapsModel
{
public:
    SinapsModel(SinapsListener *inputListener, SinapsListener *outputListener);

private:
    SinapsListener *inputListener;
    SinapsListener *outputListener;
};

#endif // SINAPSMODEL_H
