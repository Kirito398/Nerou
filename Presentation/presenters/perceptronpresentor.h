#ifndef PERCEPTRONPRESENTOR_H
#define PERCEPTRONPRESENTOR_H

#include "listeners/perceptronpresentorlistener.h"

class PerceptronViewListener;
class PerceptronInteractorListener;

class PerceptronPresentor : public PerceptronPresentorListener
{
public:
    PerceptronPresentor();
    ~PerceptronPresentor();
    void setView(PerceptronViewListener *listener);
    void setInteractor(PerceptronInteractorListener *listener);
    void setPosition(double x, double y);
    unsigned long getID();
    void setOutputNeuron(bool enable);
    bool isOutputNeuron();

private:
    void updatePosition(double x, double y) override;
    void setActive(bool enable) override;
    void setOutValue(double value) override;

private:
    PerceptronViewListener *view;
    PerceptronInteractorListener *interactor;
};

#endif // PERCEPTRONPRESENTOR_H
