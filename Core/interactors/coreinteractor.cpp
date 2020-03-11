#include "coreinteractor.h"

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"

CoreInteractor::CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : CoreInterface(inputListener, outputListener)
{

}

void CoreInteractor::init() {

}

void CoreInteractor::sendSignal(double *signal, unsigned int row, unsigned int column) {

}

double **CoreInteractor::getValue() {

}

void CoreInteractor::deleteSinaps() {
    removeSinaps();
}
