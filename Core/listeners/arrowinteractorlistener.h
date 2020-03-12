#ifndef ARROWPRESENTORLISTENER_H
#define ARROWPRESENTORLISTENER_H

class SinapsPresentorListener;

class ArrowInteractorListener
{
public:
    virtual void deleteSinaps() = 0;
    virtual void setView(SinapsPresentorListener *listener) = 0;
};

#endif // ARROWPRESENTORLISTENER_H
