#include "coreinteractor.h"

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"

CoreInteractor::CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : CoreInterface(inputListener, outputListener)
{
    view = nullptr;
    value = nullptr;
    weight = nullptr;
    delta = nullptr;
    isMaxPoolingEnabled = false;
    coreSize = 3;
    maxPoolingCoreSize = 2;
}

void CoreInteractor::init() {
    if (weight != nullptr) {
        delete [] weight;
        weight = nullptr;
    }

    unsigned int size = coreSize * coreSize;
    weight = new double[size];

    for (unsigned int i = 0; i < size; i++)
        weight[i] = random();

    deleteValue();
}

void CoreInteractor::updateSinaps(double learningRange, double alpha) {

}

void CoreInteractor::sendSignal(double *signal, unsigned int row, unsigned int column) {
    validConvolution(signal, row, column);

    outputListener->onInputSignalChanged();
}

void CoreInteractor::validConvolution(double *signal, unsigned int row, unsigned int column) {
    deleteValue();

    currentRow = row - coreSize + 1;
    currentColumn = column - coreSize + 1;

    value = new double[currentRow * currentColumn];

    for (unsigned int k = 0; k < currentRow; k++) {
        for (unsigned int p = 0; p < currentColumn; p++) {
            double sum = 0;

            for (unsigned int i = 0; i < coreSize; i++)
                for (unsigned int j = 0; j < coreSize; j++)
                    sum += signal[(k + i) * currentColumn + (p + j)] * weight[i * coreSize + j];

            value[k * currentColumn + p] = sum;
        }
    }

    if (isMaxPoolingEnabled)
        maxPooling();
}

void CoreInteractor::maxPooling() {
    unsigned int newRow = currentRow + maxPoolingCoreSize - (currentRow % maxPoolingCoreSize);
    unsigned int newColumn = currentColumn + maxPoolingCoreSize - (currentColumn % maxPoolingCoreSize);

    double *temp = new double[newRow * newColumn];

    for (unsigned int i = 0; i < currentRow; i++)
        for (unsigned int j = 0; j < currentColumn; j++)
            temp[i * currentColumn + j] = value[i * currentColumn + j];

    deleteValue();

    currentRow = newRow / maxPoolingCoreSize;
    currentColumn = newColumn / maxPoolingCoreSize;

    unsigned int l = 0;
    for (unsigned int k = 0; k < newRow; k+=maxPoolingCoreSize) {
        for (unsigned int p = 0; p < newColumn; p+=maxPoolingCoreSize) {
            double max = 0;

            for (unsigned int i = 0; i < maxPoolingCoreSize; i++)
                for (unsigned int j = 0; j < maxPoolingCoreSize; j++)
                    if (temp[(k + i) * newColumn + (p + j)] > max)
                        max = temp[(k + i) * newColumn + (p + j)];

            value[l] = max;
            l++;
        }
    }
}

double *CoreInteractor::getValue() {
    return value;
}

unsigned int CoreInteractor::getRow() {
    return currentRow;
}

unsigned int CoreInteractor::getColumn() {
    return currentColumn;
}

void CoreInteractor::deleteValue() {
    if (value == nullptr)
        return;

    delete [] value;
    value = nullptr;

    currentRow = 0;
    currentColumn = 0;
}

void CoreInteractor::setView(SinapsPresentorListener *listener) {
    view = listener;
}

void CoreInteractor::deleteSinaps() {
    removeSinaps();
}
