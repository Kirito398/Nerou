#ifndef WEIGHTINTERACTOR_H
#define WEIGHTINTERACTOR_H

#include "interfaces/weightinterface.h"

class SinapsPresentorListener;

class WeightInteractor : public WeightInterface
{
public:
    WeightInteractor(SinapsListener *inputListener, SinapsListener *outputListener);
    double getValue() override;
    void sendSignal(double signal) override;
    void init() override;

private:
    double value;
    double weight;
};

#endif // WEIGHTINTERACTOR_H
