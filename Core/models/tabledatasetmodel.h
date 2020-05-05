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
    void addTrainingInputSet(std::vector<std::string> set);
    void addTestingInputSet(std::vector<std::string> set);
    void addTrainingTargetSet(std::vector<std::string> set);
    void addTestingTargetSet(std::vector<std::string> set);
    std::vector<std::string> getTrainingInputSet(size_t number);
    std::vector<std::string> getTestingInputSet(size_t number);
    std::vector<std::string> getTrainingTargetSet(size_t number);
    std::vector<std::string> getTestingTargetSet(size_t number);
    void setInputsTitles(std::vector<std::string> titles);
    void setTargetsTitles(std::vector<std::string> titles);
    std::vector<std::string> getTargetTitles();
    std::vector<std::string> getInputTitles();
    void clear();

private:
    std::string mainPath;
    std::vector<std::vector<std::string>> trainingInputSet;
    std::vector<std::vector<std::string>> testingInputSet;
    std::vector<std::vector<std::string>> trainingTargetSet;
    std::vector<std::vector<std::string>> testingTargetSet;
    std::vector<std::string> targetTitles;
    std::vector<std::string> inputTitles;
};

#endif // TABLEDATASETMODEL_H
