#ifndef DATAINTERACTORLISTENER_H
#define DATAINTERACTORLISTENER_H

class DataPresentorListener;

class DataInteractorListener
{
public:
    virtual void setView(DataPresentorListener *listener) = 0;
};

#endif // DATAINTERACTORLISTENER_H
