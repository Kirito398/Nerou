#ifndef MODELITEM_H
#define MODELITEM_H

#include <iostream>
#include <interfaces/moveiteminterface.h>

using namespace std;

class ModelItem
{
public:
    ModelItem(MoveItemInterface *listener);
    void setPosition(float posX, float posY);

private:
    float posX, posY;
    MoveItemInterface *listener = nullptr;

};

#endif // MODELITEM_H
