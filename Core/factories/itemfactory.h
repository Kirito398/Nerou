#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <map>

#include <factories/itemcreator.h>
#include <models/perceptronmodel.h>
#include <models/datamodel.h>

class ItemFactory
{
public:
    ItemFactory();
    ModelItem *create(MoveItemInterface *listener, ModelItem::ItemType type);

protected:
    typedef std::map<ModelItem::ItemType, AbstractItemCreator*> FactoryMap;
    FactoryMap factory;

private:
    template <class C>
    void add(ModelItem::ItemType type);
};

#endif // ITEMFACTORY_H
