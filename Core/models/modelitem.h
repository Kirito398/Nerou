#ifndef MODELITEM_H
#define MODELITEM_H

#include <iostream>
#include <vector>

#include <interfaces/moveiteminterface.h>

using namespace std;

class ModelItem
{
public:
    ModelItem(MoveItemInterface *listener);
    void setPosition(double posX, double posY);
    void addInputItem(ModelItem* inputItem);
    void addOutputItem(ModelItem* outputItem);

private:
    double posX, posY;
    MoveItemInterface *listener = nullptr;
    vector<ModelItem *> inputItems;
    vector<ModelItem *> outputItems;
};

#endif // MODELITEM_H
