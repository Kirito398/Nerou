#ifndef MAINPRESENTORLISTENER_H
#define MAINPRESENTORLISTENER_H

class PerceptronInteractorListener;
class DataInteractorListener;

class MainPresentorListener
{
public:
    virtual void onNewPerceptronAdded(PerceptronInteractorListener *perceptron) = 0;
    virtual void onNewDataAdded(DataInteractorListener *data) = 0;
};

#endif // MAINPRESENTORLISTENER_H
