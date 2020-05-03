#include "tabledatasetmodel.h"

TableDataSetModel::TableDataSetModel()
{
    mainPath = "";
}

std::string TableDataSetModel::getMainPath() {
    return mainPath;
}

void TableDataSetModel::setMainPath(std::string path) {
    mainPath = path;
}

void TableDataSetModel::addTrainingSet(std::vector<std::string> set) {
    trainingSet.push_back(set);
}

void TableDataSetModel::addTestingSet(std::vector<std::string> set) {
    testingSet.push_back(set);
}

std::vector<std::string> TableDataSetModel::getTrainingSet(size_t number) {
    return trainingSet[number];
}

std::vector<std::string> TableDataSetModel::getTestingSet(size_t number) {
    return testingSet[number];
}

void TableDataSetModel::setTrainingTitles(std::vector<std::string> titles) {
    trainingTitles.clear();
    trainingTitles = titles;
}

void TableDataSetModel::setTestingTitles(std::vector<std::string> titles) {
    testingTitles.clear();
    testingTitles = titles;
}

std::vector<std::string> TableDataSetModel::getTrainingTitles() {
    return trainingTitles;
}

std::vector<std::string> TableDataSetModel::getTestingTitles() {
    return testingTitles;
}

void TableDataSetModel::clear() {
    mainPath = "";
    trainingSet.clear();
    testingSet.clear();
    trainingTitles.clear();
    testingTitles.clear();
}
