#ifndef COREINTERACTOR_H
#define COREINTERACTOR_H

#include "interfaces/coreinterface.h"

class SinapsPresentorListener;

class CoreInteractor : public CoreInterface
{
public:
    CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener);

private:
    void init() override;
    void sendSignal(double *signal, unsigned int row, unsigned int column) override;
    double ** getValue() override;
};

#endif // COREINTERACTOR_H
