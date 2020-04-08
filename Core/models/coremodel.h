#ifndef COREMODEL_H
#define COREMODEL_H

#include <vector>

class CoreModel
{
public:
    CoreModel(unsigned long id);
    unsigned long getID();
    void setType(int type);
    int getType();
    void setInputNeuronID(unsigned long id);
    unsigned long getInputNeuronID();
    void setOutputNeuronID(unsigned long id);
    unsigned long getOutputNeuronID();
    void setWeight(std::vector<std::vector<double>> weight);
    std::vector<std::vector<double>> getWeight();
    void setCoreSize(unsigned long size);
    unsigned long getCoreSize();
    void setMaxPoolingCoreSize(unsigned long size);
    unsigned long getMaxPoolingCoreSize();
    void setIsMaxPoolingEnable(bool enable);
    bool getIsMaxPoolingEnable();

private:
    unsigned long id;
    int type;
    unsigned long inputNeuronID;
    unsigned long outputNeuronID;
    std::vector<std::vector<double>> weight;
    unsigned int coreSize, maxPoolingCoreSize;
    bool isMaxPoolingEnabled;
};

#endif // COREMODEL_H
