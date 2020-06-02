#include "tabledatasetmodel.h"

#include <algorithm>

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

void TableDataSetModel::addTrainingInputSet(std::vector<double> set) {
    trainingInputSet.push_back(set);

    size_t size = set.size();

    if (inputsMax.empty())
        inputsMax = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] > inputsMax[i])
            inputsMax[i] = set[i];

    if (inputsMin.empty())
        inputsMin = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] < inputsMin[i])
            inputsMin[i] = set[i];
}

void TableDataSetModel::addTestingInputSet(std::vector<double> set) {
    testingInputSet.push_back(set);

    size_t size = set.size();

    if (inputsMax.empty())
        inputsMax = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] > inputsMax[i])
            inputsMax[i] = set[i];

    if (inputsMin.empty())
        inputsMin = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] < inputsMin[i])
            inputsMin[i] = set[i];
}

void TableDataSetModel::addTrainingTargetSet(std::vector<double> set) {
    trainingTargetSet.push_back(set);

    size_t size = set.size();

    if (targetsMax.empty())
        targetsMax = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] > targetsMax[i])
            targetsMax[i] = set[i];

    if (targetsMin.empty())
        targetsMin = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] < targetsMin[i])
            targetsMin[i] = set[i];
}

void TableDataSetModel::addTestingTargetSet(std::vector<double> set) {
    testingTargetSet.push_back(set);

    size_t size = set.size();

    if (targetsMax.empty())
        targetsMax = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] > targetsMax[i])
            targetsMax[i] = set[i];

    if (targetsMin.empty())
        targetsMin = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] < targetsMin[i])
            targetsMin[i] = set[i];
}

std::vector<double> TableDataSetModel::getTrainingInputSet(size_t number) {
    return trainingInputSet[number];
}

std::vector<double> TableDataSetModel::getTestingInputSet(size_t number) {
    return testingInputSet[number];
}

std::vector<double> TableDataSetModel::getTrainingTargetSet(size_t number) {
    return trainingTargetSet[number];
}

std::vector<double> TableDataSetModel::getTestingTargetSet(size_t number) {
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

unsigned long TableDataSetModel::getTestingIterationNumber() {
    return testingInputSet.size();
}

std::vector<double> TableDataSetModel::getInputsMax() {
    return inputsMax;
}

std::vector<double> TableDataSetModel::getTargetsMax() {
    return targetsMax;
}

std::vector<double> TableDataSetModel::getInputsMin() {
    return inputsMin;
}

std::vector<double> TableDataSetModel::getTargetsMin() {
    return targetsMin;
}

std::vector<unsigned long> TableDataSetModel::getOutputsNeuronsID() {
    return outputsNeuronsID;
}

void TableDataSetModel::setOutputsNeuronsID(std::vector<unsigned long> outputsNeuronsID) {
    this->outputsNeuronsID = outputsNeuronsID;
}

void TableDataSetModel::shuffleData() {
    std::random_shuffle(trainingInputSet.begin(), trainingInputSet.end());
    std::random_shuffle(testingInputSet.begin(), testingInputSet.end());
    std::random_shuffle(trainingTargetSet.begin(), trainingTargetSet.end());
    std::random_shuffle(testingTargetSet.begin(), testingTargetSet.end());
}

void TableDataSetModel::clear() {
    mainPath = "";
    trainingInputSet.clear();
    testingInputSet.clear();
    trainingTargetSet.clear();
    testingTargetSet.clear();
    targetTitles.clear();
    inputTitles.clear();
    inputsMax.clear();
    targetsMax.clear();
    inputsMin.clear();
    targetsMin.clear();
    outputsNeuronsID.clear();
}
