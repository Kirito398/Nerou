#ifndef MAINPRESENTORLISTENER_H
#define MAINPRESENTORLISTENER_H

class PerceptronInteractorListener;

class MainPresentorListener
{
public:
    virtual void onNewPerceptronCreated(PerceptronInteractorListener *perceptron) = 0;
};

#endif // MAINPRESENTORLISTENER_H
