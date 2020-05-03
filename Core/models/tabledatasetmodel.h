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
    void addTrainingSet(std::vector<std::string> set);
    void addTestingSet(std::vector<std::string> set);
    std::vector<std::string> getTrainingSet(size_t number);
    std::vector<std::string> getTestingSet(size_t number);
    void setTrainingTitles(std::vector<std::string> titles);
    void setTestingTitles(std::vector<std::string> titles);
    std::vector<std::string> getTrainingTitles();
    std::vector<std::string> getTestingTitles();
    void clear();

private:
    std::string mainPath;
    std::vector<std::vector<std::string>> trainingSet;
    std::vector<std::vector<std::string>> testingSet;
    std::vector<std::string> trainingTitles;
    std::vector<std::string> testingTitles;
};

#endif // TABLEDATASETMODEL_H
