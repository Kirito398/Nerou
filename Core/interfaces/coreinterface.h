#ifndef COREINTERFACE_H
#define COREINTERFACE_H

#include <vector>

#include "interactors/sinapsinteractor.h"

class CoreInterface : public SinapsInteractor
{
public:
    CoreInterface(SinapsListener *inputListener, SinapsListener *outputListener) : SinapsInteractor(inputListener, outputListener, Core) {}
    virtual std::vector<std::vector<double>> getValue() = 0;
    virtual void sendSignal(std::vector<std::vector<double>> value) = 0;
    virtual std::vector<std::vector<double>> getDelta() = 0;
    virtual void sendDelta(std::vector<std::vector<double>> delta) = 0;
};

#endif // COREINTERFACE_H
