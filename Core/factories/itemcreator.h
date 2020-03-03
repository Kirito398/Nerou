#ifndef ITEMCREATOR_H
#define ITEMCREATOR_H

#include <factories/abstractitemcreator.h>

template <class C>
class ItemCreator : public AbstractItemCreator
{
public:
    virtual ModelItem * create(MoveItemInterface *listener) const override {return new C(listener);}
};

#endif // ITEMCREATOR_H
