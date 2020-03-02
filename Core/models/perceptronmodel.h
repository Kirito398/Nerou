#ifndef PERCEPTRONMODEL_H
#define PERCEPTRONMODEL_H

#include <models/modelitem.h>
#include <models/weightmodel.h>

class PerceptronModel : public ModelItem
{
public:
    PerceptronModel(MoveItemInterface *listener);
    void onInputSignalChanged() override;

private:
    void makeInputSignal();
    void calculateOut();
    void sendSignal();
    void clearInputSignal();

private:
    unsigned long inputSignalCount;
    double *inputSignal;
    double outValue;
};

#endif // PERCEPTRONMODEL_H
