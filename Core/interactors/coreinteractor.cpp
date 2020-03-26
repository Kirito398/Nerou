#include "coreinteractor.h"

#include <limits>

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"

CoreInteractor::CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : CoreInterface(inputListener, outputListener)
{
    view = nullptr;
    value = nullptr;
    weight = nullptr;
    delta = nullptr;
    maxValue = nullptr;
    isMaxPoolingEnabled = true;
    coreSize = 5;
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

    //deleteValue();
}

void CoreInteractor::updateSinaps(double learningRange, double alpha) {

}

void CoreInteractor::sendSignal(double *signal, unsigned int row, unsigned int column) {
    view->setActive(true);
    validConvolution(signal, row, column);

    outputListener->onInputSignalChanged();
    view->setActive(false);
}

double *CoreInteractor::convolution(double *input, unsigned int row, unsigned int column) {
    currentRow = row - coreSize + 1;
    currentColumn = column - coreSize + 1;

    double *output = new double[currentRow * currentColumn];

    for (unsigned int k = 0; k < currentRow; k++) {
        for (unsigned int p = 0; p < currentColumn; p++) {
            double sum = 0;

            for (unsigned int i = 0; i < coreSize; i++)
                for (unsigned int j = 0; j < coreSize; j++)
                    sum += input[(k + i) * currentColumn + (p + j)] * weight[i * coreSize + j];

            output[k * currentColumn + p] = sum;
        }
    }

    return output;
}

void CoreInteractor::validConvolution(double *signal, unsigned int row, unsigned int column) {
    //deleteValue();

    value = convolution(signal, row, column);

    if (isMaxPoolingEnabled)
        maxPooling();
}

void CoreInteractor::maxPooling() {
    unsigned int newRow = currentRow + (currentRow % maxPoolingCoreSize);
    unsigned int newColumn = currentColumn + (currentColumn % maxPoolingCoreSize);

    double *temp = new double[newRow * newColumn];
    double min = - std::numeric_limits<double>::max();

    for (unsigned int i = 0; i < currentRow; i++)
        for (unsigned int j = 0; j < currentColumn; j++)
            temp[i * currentColumn + j] = min;

    for (unsigned int i = 0; i < currentRow; i++)
        for (unsigned int j = 0; j < currentColumn; j++)
            temp[i * currentColumn + j] = value[i * currentColumn + j];

    deleteValue();
    //deleteMaxValue();

    maxValue = new bool[newRow * newColumn];

    for (unsigned int i = 0; i < newRow; i++)
        for (unsigned int j = 0; j < newColumn; j++)
            maxValue[i * newColumn + j] = false;

    currentRow = newRow / maxPoolingCoreSize;
    currentColumn = newColumn / maxPoolingCoreSize;

    value = new double[currentRow * currentColumn];

    unsigned int l = 0;
    for (unsigned int k = 0; k < newRow; k+=maxPoolingCoreSize) {
        for (unsigned int p = 0; p < newColumn; p+=maxPoolingCoreSize) {
            double max = temp[k * newColumn + p];
            int maxI = k, maxJ = p;

            for (unsigned int i = 0; i < maxPoolingCoreSize; i++)
                for (unsigned int j = 0; j < maxPoolingCoreSize; j++)
                    if (temp[(k + i) * newColumn + (p + j)] > max) {
                        max = temp[(k + i) * newColumn + (p + j)];
                        maxI = k + i;
                        maxJ = p + j;
                    }

            maxValue[maxI * newColumn + maxJ] = true;
            value[l] = max;
            l++;
        }
    }

    delete [] temp;
}

void CoreInteractor::revConvolution(double *delta) {
    if (isMaxPoolingEnabled)
        maxPoolingRev(delta);

    unsigned int deltaCore = coreSize - 1;
    unsigned int newRow = deltaCore * 2 + currentRow;
    unsigned int newColumn = deltaCore * 2 + currentColumn;

    double *temp = new double[newRow * newColumn];
    for (unsigned int i = 0; i < newRow; i++)
        for (unsigned int j = 0; j < newColumn; j++)
            temp[i * newColumn + j] = 0;

    for (unsigned int i = 0; i < currentRow; i++)
        for (unsigned int j = 0; j < currentColumn; j++)
            temp[(i + deltaCore) * currentColumn + (j + deltaCore)] = delta[i * currentColumn + j];

    //deleteDelta();
    this->delta = convolution(temp, newRow, newColumn);

    delete [](temp);
}

void CoreInteractor::maxPoolingRev(double *delta) {
    unsigned int newRow = currentRow * maxPoolingCoreSize;
    unsigned int newColumn = currentColumn * maxPoolingCoreSize;

    double *temp = new double[newRow * newColumn];

    unsigned int l = 0;
    for (unsigned int i = 0; i < newRow; i++) {
        for (unsigned int j = 0; j < newColumn; j++) {
            if (maxValue[i * newColumn + j]) {
                temp[i * newColumn + j] = delta[l];
                l++;
            } else {
                temp[i * newColumn + j] = 0;
            }
        }
    }

    delete [] delta;
    delta = temp;
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

double *CoreInteractor::getDelta() {
    return delta;
}

void CoreInteractor::sendDelta(double *delta) {
    revConvolution(delta);
    inputListener->onDeltaValueChanged();
}

void CoreInteractor::deleteValue() {
    if (value == nullptr)
        return;

    delete [](value);
    value = nullptr;

    currentRow = 0;
    currentColumn = 0;
}

void CoreInteractor::deleteMaxValue() {
    if (maxValue == nullptr)
        return;

    delete [] maxValue;
    maxValue = nullptr;
}

void CoreInteractor::deleteDelta() {
    if (delta == nullptr)
        return;

    delete [] delta;
    delta = nullptr;
}

void CoreInteractor::setView(SinapsPresentorListener *listener) {
    view = listener;
}

void CoreInteractor::deleteSinaps() {
    removeSinaps();
}
