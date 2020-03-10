#ifndef ARROWPRESENTOR_H
#define ARROWPRESENTOR_H

#include "listeners/sinapspresentorlistener.h"

class ArrowViewListener;
class ArrowInteractorListener;

class ArrowPresentor : public SinapsPresentorListener
{
public:
    ArrowPresentor();
    ~ArrowPresentor();
    void setView(ArrowViewListener *listener);
    void setInteractor(ArrowInteractorListener *listener);

private:
    ArrowViewListener *view;
    ArrowInteractorListener *interactor;
};

#endif // ARROWPRESENTOR_H
