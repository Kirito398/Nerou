#ifndef SINAPSFACTORY_H
#define SINAPSFACTORY_H

#include <map>

#include <models/weightmodel.h>
#include <factories/sinapscreator.h>

class SinapsFactory
{
public:
    SinapsFactory();
    SinapsModel *create(SinapsListener *inputListener, SinapsListener *outputListener, SinapsModel::SinapsType type);

protected:
    typedef std::map<SinapsModel::SinapsType, AbstractSinapsCreator*> FactoryMap;
    FactoryMap factory;

private:
    template <class C>
    void add(SinapsModel::SinapsType type);
};

#endif // SINAPSFACTORY_H
