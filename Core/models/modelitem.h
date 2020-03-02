#ifndef MODELITEM_H
#define MODELITEM_H

#include <iostream>
#include <vector>
#include <math.h>

#include <interfaces/moveiteminterface.h>
#include <models/weightmodel.h>

using namespace std;

class ModelItem : public SinapsListener
{
public:
    enum ItemType {Perceptron, Convolution, VectorData};

public:
    ModelItem(MoveItemInterface *listener, ItemType type);
    void setPosition(double posX, double posY);
    void addInputSinaps(SinapsModel* inputItem);
    void addOutputSinaps(SinapsModel* outputItem);
    void removeInputSinaps(SinapsModel *inputItem);
    void removeOutputSinaps(SinapsModel *outputItem);
    MoveItemInterface *getListener();
    ItemType getType();

protected:
    double activateFunction(double value);

protected:
    MoveItemInterface *listener = nullptr;
    vector<SinapsModel *> inputItems;
    vector<SinapsModel *> outputItems;

private:
    double posX, posY;
    ItemType type;
};

#endif // MODELITEM_H
