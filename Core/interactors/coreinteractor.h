#ifndef COREINTERACTOR_H
#define COREINTERACTOR_H

#include "interfaces/coreinterface.h"

class SinapsPresentorListener;

class CoreInteractor : public CoreInterface
{
public:
    CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener);
};

#endif // COREINTERACTOR_H
