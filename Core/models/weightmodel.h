#ifndef WEIGHTMODEL_H
#define WEIGHTMODEL_H

#include <models/sinapsmodel.h>

class WeightModel : public SinapsModel
{
public:
    WeightModel(SinapsListener *inputListener, SinapsListener *outputListener);
    double getValue();
    void sendSignal(double signal);
    void init() override;

private:
    double value;
    double weight;
};

#endif // WEIGHTMODEL_H
