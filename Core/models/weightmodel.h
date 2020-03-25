#ifndef WEIGHTMODEL_H
#define WEIGHTMODEL_H


class WeightModel
{
public:
    WeightModel(unsigned long id);
    unsigned long getID();
    void setType(int type);
    int getType();
    void setInputNeuronID(unsigned long id);
    unsigned long getInputNeuronID();
    void setOutputNeuronID(unsigned long id);
    unsigned long getOutputNeuronID();
    void setWeight(double weight);
    double getWeight();

private:
    unsigned long id;
    int type;
    unsigned long inputNeuronID;
    unsigned long outputNeuronID;
    double weight;
};

#endif // WEIGHTMODEL_H
