#ifndef ABSTRACTITEMCREATOR_H
#define ABSTRACTITEMCREATOR_H

#include "models/modelitem.h"

class AbstractItemCreator
{
public:
    virtual ModelItem *create(MoveItemInterface *listener) const = 0;
};

#endif // ABSTRACTITEMCREATOR_H
