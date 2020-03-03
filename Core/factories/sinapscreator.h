#ifndef SINAPSCREATOR_H
#define SINAPSCREATOR_H

#include "factories/abstractsinapscreator.h"

template <class C>
class SinapsCreator : public AbstractSinapsCreator
{
public:
    virtual SinapsModel * create(SinapsListener *inputListener, SinapsListener *outputListener) const override {return new C(inputListener, outputListener);}
};

#endif // SINAPSCREATOR_H
