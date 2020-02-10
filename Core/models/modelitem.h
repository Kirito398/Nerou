#ifndef MODELITEM_H
#define MODELITEM_H

#include <iostream>
#include <interfaces/moveiteminterface.h>

using namespace std;

class ModelItem
{
public:
    ModelItem(string objectName, MoveItemInterface *listener);
    void setPosition(float posX, float posY);
    string objectName;

private:
    float posX, posY;
    MoveItemInterface *listener = nullptr;

};

#endif // MODELITEM_H
