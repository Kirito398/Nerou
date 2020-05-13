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

void TableDataSetModel::addTrainingInputSet(std::vector<double> set) {
    trainingInputSet.push_back(set);

    size_t size = set.size();

    if (trainingInputsMax.empty())
        trainingInputsMax = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] > trainingInputsMax[i])
            trainingInputsMax[i] = set[i];

    if (trainingInputsMin.empty())
        trainingInputsMin = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] < trainingInputsMin[i])
            trainingInputsMin[i] = set[i];
}

void TableDataSetModel::addTestingInputSet(std::vector<double> set) {
    testingInputSet.push_back(set);

    size_t size = set.size();

    if (testingInputsMax.empty())
        testingInputsMax = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] > testingInputsMax[i])
            testingInputsMax[i] = set[i];

    if (testingInputsMin.empty())
        testingInputsMin = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] < testingInputsMin[i])
            testingInputsMin[i] = set[i];
}

void TableDataSetModel::addTrainingTargetSet(std::vector<double> set) {
    trainingTargetSet.push_back(set);

    size_t size = set.size();

    if (trainingTargetsMax.empty())
        trainingTargetsMax = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] > trainingTargetsMax[i])
            trainingTargetsMax[i] = set[i];

    if (trainingTargetsMin.empty())
        trainingTargetsMin = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] < trainingTargetsMin[i])
            trainingTargetsMin[i] = set[i];
}

void TableDataSetModel::addTestingTargetSet(std::vector<double> set) {
    testingTargetSet.push_back(set);

    size_t size = set.size();

    if (testingTargetsMax.empty())
        testingTargetsMax = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] > testingTargetsMax[i])
            testingTargetsMax[i] = set[i];

    if (testingTargetsMin.empty())
        testingTargetsMin = set;

    for (size_t i = 0; i < size; i++)
        if (set[i] < testingTargetsMin[i])
            testingTargetsMin[i] = set[i];
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

std::vector<double> TableDataSetModel::getTrainingInputsMax() {
    return trainingInputsMax;
}

std::vector<double> TableDataSetModel::getTestingInputsMax() {
    return testingInputsMax;
}

std::vector<double> TableDataSetModel::getTrainingTargetsMax() {
    return trainingTargetsMax;
}

std::vector<double> TableDataSetModel::getTestingTargetsMax() {
    return testingTargetsMax;
}

std::vector<double> TableDataSetModel::getTrainingInputsMin() {
    return trainingInputsMin;
}

std::vector<double> TableDataSetModel::getTestingInputsMin() {
    return testingInputsMin;
}

std::vector<double> TableDataSetModel::getTrainingTargetsMin() {
    return trainingTargetsMin;
}

std::vector<double> TableDataSetModel::getTestingTargetsMin() {
    return testingTargetsMin;
}

std::vector<unsigned long> TableDataSetModel::getOutputsNeuronsID() {
    return outputsNeuronsID;
}

void TableDataSetModel::setOutputsNeuronsID(std::vector<unsigned long> outputsNeuronsID) {
    this->outputsNeuronsID = outputsNeuronsID;
}

void TableDataSetModel::clear() {
    mainPath = "";
    trainingInputSet.clear();
    testingInputSet.clear();
    trainingTargetSet.clear();
    testingTargetSet.clear();
    targetTitles.clear();
    inputTitles.clear();
    trainingInputsMax.clear();
    testingInputsMax.clear();
    trainingTargetsMax.clear();
    testingTargetsMax.clear();
    trainingInputsMin.clear();
    testingInputsMin.clear();
    trainingTargetsMin.clear();
    testingTargetsMin.clear();
    outputsNeuronsID.clear();
}
