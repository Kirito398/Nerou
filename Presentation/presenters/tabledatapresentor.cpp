#include "tabledatapresentor.h"

#include <QString>
#include <QStringList>
#include <QVector>
#include <string>
#include <vector>

#include "listeners/tabledataviewlistener.h"

TableDataPresentor::TableDataPresentor()
{
    interactor = nullptr;
    view = nullptr;
}

void TableDataPresentor::setView(TableDataViewListener *listener) {
    view = listener;
}

void TableDataPresentor::setInteractor(TableDataInteractorListener *listener) {
    interactor = listener;
    interactor->setView(this);
}

QVector<QStringList> TableDataPresentor::loadTableValue(QString path) {
    QVector<QStringList> newVector;
    std::vector<std::vector<std::string>> vector = interactor->loadTableValue(path.toStdString());

    for (unsigned long i = 0; i < vector.size(); i++) {
        QStringList newList;

        for (unsigned long j = 0; j < vector[i].size(); j++)
            newList.append(QString::fromStdString(vector[i][j]));

        newVector.append(newList);
    }

    return newVector;
}

void TableDataPresentor::setPosition(double x, double y) {
    interactor->setPosition(x, y);
}

unsigned long TableDataPresentor::getID() {
    return interactor->getID();
}

void TableDataPresentor::setActivateFunctionType(int type) {
    interactor->setActivateFunctionType(type);
}

int TableDataPresentor::getActivateFunctionType() {
    return interactor->getActivateFunctiontype();
}

void TableDataPresentor::setLossFunctionType(LossFunctionType type) {
    interactor->setLossFunctionType(type);
}

LossFunctionType TableDataPresentor::getLossFunctionType() {
    return interactor->getLossFunctionType();
}

void TableDataPresentor::updatePosition(double x, double y) {
    view->updatePosition(x, y);
}

QString TableDataPresentor::getDataSetMainPath() {
    return QString::fromStdString(interactor->getDataSetMainPath());
}

void TableDataPresentor::setDataSetMainPath(QString path) {
    interactor->setDataSetMainPath(path.toStdString());
}

void TableDataPresentor::addTrainingInputSet(QStringList set) {
    std::vector<std::string> stdSet;

    for (auto item : set)
        stdSet.push_back(item.toStdString());

    interactor->addTrainingInputSet(stdSet);
}

void TableDataPresentor::addTestingInputSet(QStringList set) {
    std::vector<std::string> stdSet;

    for (auto item : set)
        stdSet.push_back(item.toStdString());

    interactor->addTestingInputSet(stdSet);
}

void TableDataPresentor::addTrainingTargetSet(QStringList set) {
    std::vector<std::string> stdSet;

    for (auto item : set)
        stdSet.push_back(item.toStdString());

    interactor->addTrainingTargetSet(stdSet);
}

void TableDataPresentor::addTestingTargetSet(QStringList set) {
    std::vector<std::string> stdSet;

    for (auto item : set)
        stdSet.push_back(item.toStdString());

    interactor->addTestingTargetSet(stdSet);
}

void TableDataPresentor::setTargetTitles(QStringList titles) {
    std::vector<std::string> stdTitles;

    for (auto item : titles)
        stdTitles.push_back(item.toStdString());

    interactor->setTargetTitles(stdTitles);
}

void TableDataPresentor::setInputsTitles(QStringList titles) {
    std::vector<std::string> stdTitles;

    for (auto item : titles)
        stdTitles.push_back(item.toStdString());

    interactor->setInputsTitles(stdTitles);
}

QStringList TableDataPresentor::getInputsTitles() {
    QStringList titles;

    std::vector<std::string> stdTitles = interactor->getInputsTitles();

    for (auto title : stdTitles)
        titles.append(QString::fromStdString(title));

    return titles;
}

QStringList TableDataPresentor::getTargetTitles() {
    QStringList titles;

    std::vector<std::string> stdTitles = interactor->getTargetTitles();

    for (auto title : stdTitles)
        titles.append(QString::fromStdString(title));

    return titles;
}

void TableDataPresentor::clearDataSet() {
    interactor->clearDataSet();
}

TableDataPresentor::~TableDataPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();;
}
