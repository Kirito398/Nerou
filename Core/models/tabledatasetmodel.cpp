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

void TableDataSetModel::addTrainingInputSet(std::vector<std::string> set) {
    trainingInputSet.push_back(set);
}

void TableDataSetModel::addTestingInputSet(std::vector<std::string> set) {
    testingInputSet.push_back(set);
}

void TableDataSetModel::addTrainingTargetSet(std::vector<std::string> set) {
    trainingTargetSet.push_back(set);
}

void TableDataSetModel::addTestingTargetSet(std::vector<std::string> set) {
    testingTargetSet.push_back(set);
}

std::vector<std::string> TableDataSetModel::getTrainingInputSet(size_t number) {
    return trainingInputSet[number];
}

std::vector<std::string> TableDataSetModel::getTestingInputSet(size_t number) {
    return testingInputSet[number];
}

std::vector<std::string> TableDataSetModel::getTrainingTargetSet(size_t number) {
    return trainingTargetSet[number];
}

std::vector<std::string> TableDataSetModel::getTestingTargetSet(size_t number) {
    return testingTargetSet[number];
}

void TableDataSetModel::setInputsTitles(std::vector<std::string> titles) {
    inputTitles.clear();
    inputTitles = titles;
}

void TableDataSetModel::setTargetsTitles(std::vector<std::string> titles) {
    targetTitles.clear();
    targetTitles = titles;
}

std::vector<std::string> TableDataSetModel::getTargetTitles() {
    return targetTitles;
}

std::vector<std::string> TableDataSetModel::getInputTitles() {
    return inputTitles;
}

unsigned long TableDataSetModel::getTrainingIterationNumber() {
    return trainingInputSet.size();
}

void TableDataSetModel::clear() {
    mainPath = "";
    trainingInputSet.clear();
    testingInputSet.clear();
    trainingTargetSet.clear();
    testingTargetSet.clear();
    targetTitles.clear();
    inputTitles.clear();
}
