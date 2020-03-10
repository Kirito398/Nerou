#include "arrowpresentor.h"

#include "listeners/arrowviewlistener.h"

ArrowPresentor::ArrowPresentor()
{

}

void ArrowPresentor::setView(ArrowViewListener *listener) {
    view = listener;
}

void ArrowPresentor::setInteractor(ArrowInteractorListener *listener) {
    interactor = listener;
}
