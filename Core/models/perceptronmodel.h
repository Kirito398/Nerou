#ifndef PERCEPTRONMODEL_H
#define PERCEPTRONMODEL_H

#include <models/modelitem.h>

class PerceptronModel : public ModelItem
{
public:
    PerceptronModel(MoveItemInterface *listener);
    void onInputSignalChanged() override;

private:
    void makeInputSignal();

private:
    unsigned long inputSignalCount;
};

#endif // PERCEPTRONMODEL_H
