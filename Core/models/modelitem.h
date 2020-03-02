#ifndef MODELITEM_H
#define MODELITEM_H

#include <iostream>
#include <vector>

#include <interfaces/moveiteminterface.h>
#include <listeners/SinapsListener.h>
#include <models/sinapsmodel.h>

using namespace std;

class ModelItem : public SinapsListener
{
public:
    ModelItem(MoveItemInterface *listener);
    void setPosition(double posX, double posY);
    void addInputSinaps(SinapsModel* inputItem);
    void addOutputSinaps(SinapsModel* outputItem);
    void removeInputSinaps(SinapsModel *inputItem);
    void removeOutputSinaps(SinapsModel *outputItem);
    MoveItemInterface *getListener();

private:
    double posX, posY;
    MoveItemInterface *listener = nullptr;
    vector<SinapsModel *> inputItems;
    vector<SinapsModel *> outputItems;
};

#endif // MODELITEM_H
