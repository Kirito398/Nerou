#include "sinapsfactory.h"

#include "models/weightmodel.h"

SinapsFactory::SinapsFactory()
{
    add<WeightModel>(SinapsModel::Weigth);
}

template <class C>
void SinapsFactory::add(SinapsModel::SinapsType type) {
    if (factory.find(type) == factory.end())
        factory[type] = new SinapsCreator<C>();
}

SinapsModel *SinapsFactory::create(SinapsListener *inputListener, SinapsListener *outputListener, SinapsModel::SinapsType type) {
    return factory.find(type)->second->create(inputListener, outputListener);
}
