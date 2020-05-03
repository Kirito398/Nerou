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

TableDataPresentor::~TableDataPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();;
}
