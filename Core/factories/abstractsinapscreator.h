#ifndef ABSTRACTSINAPSCREATOR_H
#define ABSTRACTSINAPSCREATOR_H

#include "models/sinapsmodel.h"

class AbstractSinapsCreator
{
public:
    virtual SinapsModel *create(SinapsListener *inputListener, SinapsListener *outputListener) const = 0;
};

#endif // ABSTRACTSINAPSCREATOR_H
