#include "coreinteractor.h"

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"

CoreInteractor::CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : CoreInterface(inputListener, outputListener)
{

}
