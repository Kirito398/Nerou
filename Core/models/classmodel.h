#ifndef CLASSMODEL_H
#define CLASSMODEL_H

#include <string>
#include <vector>

class ClassModel
{
public:
    ClassModel(unsigned long neuronID);
    void setTrainingPathsList(std::vector<std::string> list);
    void setTestingPathslist(std::vector<std::string> list);
    std::vector<std::string> getTestingPathsList();
    std::vector<std::string> getTrainingPathsList();
    unsigned long getNeuronID();

private:
    std::vector<std::string> trainingPathsList;
    std::vector<std::string> testingPathsList;
    unsigned long neuronID;
};

#endif // CLASSMODEL_H
