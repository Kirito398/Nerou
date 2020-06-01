#include "classmodel.h"

#include <algorithm>

ClassModel::ClassModel(unsigned long neuronID)
{
    this->neuronID = neuronID;
    trainingMainPath = "";
    testingMainPath = "";
    trainingPathsList.clear();
    testingPathsList.clear();
}

void ClassModel::setTrainingPathsList(std::vector<std::string> list) {
    trainingPathsList.clear();
    trainingPathsList.swap(list);

    std::random_shuffle(trainingPathsList.begin(), trainingPathsList.end());
}

void ClassModel::setTestingPathslist(std::vector<std::string> list) {
    testingPathsList.clear();
    testingPathsList.swap(list);
}

std::vector<std::string> ClassModel::getTestingPathsList() {
    return testingPathsList;
}

std::vector<std::string> ClassModel::getTrainingPathsList() {
    return trainingPathsList;
}

unsigned long ClassModel::getNeuronID() {
    return neuronID;
}

void ClassModel::setTrainingMainPath(std::string path) {
    trainingMainPath = path;
}

void ClassModel::setTestingMainPath(std::string path){
    testingMainPath = path;
}

std::string ClassModel::getTrainingMainPath() {
    return trainingMainPath;
}

std::string ClassModel::getTestingMainPath() {
    return testingMainPath;
}
