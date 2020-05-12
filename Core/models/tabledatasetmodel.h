#ifndef TABLEDATASETMODEL_H
#define TABLEDATASETMODEL_H

#include <string>
#include <vector>

class TableDataSetModel
{
public:
    TableDataSetModel();
    std::string getMainPath();
    void setMainPath(std::string path);
    void addTrainingInputSet(std::vector<double> set);
    void addTestingInputSet(std::vector<double> set);
    void addTrainingTargetSet(std::vector<double> set);
    void addTestingTargetSet(std::vector<double> set);
    std::vector<double> getTrainingInputSet(size_t number);
    std::vector<double> getTestingInputSet(size_t number);
    std::vector<double> getTrainingTargetSet(size_t number);
    std::vector<double> getTestingTargetSet(size_t number);
    void setInputsTitles(std::vector<std::string> titles);
    void setTargetsTitles(std::vector<std::string> titles);
    std::vector<std::string> getTargetTitles();
    std::vector<std::string> getInputTitles();
    void clear();
    unsigned long getTrainingIterationNumber();
    std::vector<double> getTrainingInputsMax();
    std::vector<double> getTestingInputsMax();
    std::vector<double> getTrainingTargetsMax();
    std::vector<double> getTestingTargetsMax();
    std::vector<double> getTrainingInputsMin();
    std::vector<double> getTestingInputsMin();
    std::vector<double> getTrainingTargetsMin();
    std::vector<double> getTestingTargetsMin();
    std::vector<unsigned long> getOutputsNeuronsID();
    void setOutputsNeuronsID(std::vector<unsigned long> outputsNeuronsID);

private:
    std::string mainPath;
    std::vector<std::vector<double>> trainingInputSet;
    std::vector<std::vector<double>> testingInputSet;
    std::vector<std::vector<double>> trainingTargetSet;
    std::vector<std::vector<double>> testingTargetSet;
    std::vector<std::string> targetTitles;
    std::vector<std::string> inputTitles;
    std::vector<double> trainingInputsMax;
    std::vector<double> testingInputsMax;
    std::vector<double> trainingTargetsMax;
    std::vector<double> testingTargetsMax;
    std::vector<double> trainingInputsMin;
    std::vector<double> testingInputsMin;
    std::vector<double> trainingTargetsMin;
    std::vector<double> testingTargetsMin;
    std::vector<unsigned long> outputsNeuronsID;
};

#endif // TABLEDATASETMODEL_H
