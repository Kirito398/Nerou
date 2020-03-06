#ifndef PERCEPTRONINTERACTORLISTENER_H
#define PERCEPTRONINTERACTORLISTENER_H

class PerceptronPresentorListener;

class PerceptronInteractorListener
{
public:
    virtual void setView(PerceptronPresentorListener *listener) = 0;
};

#endif // PERCEPTRONINTERACTORLISTENER_H
