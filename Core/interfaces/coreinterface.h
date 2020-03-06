#ifndef COREINTERFACE_H
#define COREINTERFACE_H

#include "interactors/sinapsinteractor.h"

class CoreInterface : public SinapsInteractor
{
public:
    CoreInterface(SinapsListener *inputListener, SinapsListener *outputListener);
};

#endif // COREINTERFACE_H
