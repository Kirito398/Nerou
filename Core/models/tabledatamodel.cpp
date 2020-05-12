#include "tabledatamodel.h"

TableDataModel::TableDataModel()
{
    posX = 0;
    posY = 0;
    id = 0;
    isOutput = false;
    type = -1;
    dataSet = nullptr;
}

double TableDataModel::getX() {
    return posX;
}

void TableDataModel::setX(double value) {
    posX = value;
}

double TableDataModel::getY() {
    return posY;
}

void TableDataModel::setY(double value) {
    posY = value;
}

unsigned long TableDataModel::getID() {
    return  id;
}

void TableDataModel::setID(unsigned long id) {
    this->id = id;
}

bool TableDataModel::getIsOutput() {
    return isOutput;
}

void TableDataModel::setIsOutput(bool enable) {
    isOutput = enable;
}

int TableDataModel::getType() {
    return type;
}

void TableDataModel::setType(int type) {
    this->type = type;
}

TableDataSetModel *TableDataModel::getDataSet() {
    return dataSet;
}

void TableDataModel::setDataSet(TableDataSetModel *model) {
    dataSet = model;
}

int TableDataModel::getActivateFunctionType() {
    return activateFunctionType;
}

void TableDataModel::setActivateFunctionType(int type) {
    activateFunctionType = type;
}

int TableDataModel::getLossFunctionType() {
    return lossFunctionType;
}

void TableDataModel::setLossFunctionType(int type) {
    lossFunctionType = type;
}
