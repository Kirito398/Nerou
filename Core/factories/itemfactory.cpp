#include "itemfactory.h"

#include <models/perceptronmodel.h>
#include <models/datamodel.h>

ItemFactory::ItemFactory()
{
    add<PerceptronModel>(ModelItem::Perceptron);
    add<PerceptronModel>(ModelItem::Convolution);
    add<DataModel>(ModelItem::VectorData);
}

template <class C>
void ItemFactory::add(ModelItem::ItemType type) {
    if (factory.find(type) == factory.end())
        factory[type] = new ItemCreator<C>();
}

ModelItem *ItemFactory::create(MoveItemInterface *listener, ModelItem::ItemType type) {
    return factory.find(type)->second->create(listener);
}
