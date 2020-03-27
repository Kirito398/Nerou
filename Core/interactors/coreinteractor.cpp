#include "coreinteractor.h"

#include <limits>

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"
#include "models/coremodel.h"

CoreInteractor::CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : CoreInterface(inputListener, outputListener)
{
    view = nullptr;
    isMaxPoolingEnabled = true;
    coreSize = 5;
    maxPoolingCoreSize = 2;

    init();
}

void CoreInteractor::init() {
    weight.clear();

    for (unsigned int i = 0; i < coreSize; i++) {
        weight.push_back(std::vector<double>());
        for (unsigned int j = 0; j < coreSize; j++) {
            weight[i].push_back(random());
        }
    }
}

void CoreInteractor::updateSinaps(double learningRange, double alpha) {

}

void CoreInteractor::sendSignal(std::vector<std::vector<double>> signal) {
    view->setActive(true);
    validConvolution(signal);

    outputListener->onInputSignalChanged();
    view->setActive(false);
}

std::vector<std::vector<double>> CoreInteractor::convolution(std::vector<std::vector<double>> input, std::vector<std::vector<double>> core) {
    unsigned int coreSize = core.size();
    unsigned int newRow = input.size() - coreSize + 1;
    unsigned int newColumn = input[0].size() - coreSize + 1;

    std::vector<std::vector<double>> output;
    for (unsigned int i = 0; i < newRow; i++)
        output.push_back(std::vector<double>(newColumn));

    for (unsigned int k = 0; k < newRow; k++) {
        for (unsigned int p = 0; p < newColumn; p++) {
            double sum = 0;

            for (unsigned int i = 0; i < coreSize; i++)
                for (unsigned int j = 0; j < coreSize; j++)
                    sum += input[k + i][p + j] * core[i][j];

            output[k][p] = sum;
        }
    }

    return output;
}

void CoreInteractor::validConvolution(std::vector<std::vector<double> > signal) {
    value.clear();
    value = convolution(signal, weight);

    if (isMaxPoolingEnabled)
        maxPooling();
}

void CoreInteractor::maxPooling() {
    unsigned int currentRow = value.size();
    unsigned int currentColumn = value[0].size();
    unsigned int newRow = currentRow + (currentRow % maxPoolingCoreSize);
    unsigned int newColumn = currentColumn + (currentColumn % maxPoolingCoreSize);

    double *temp = new double[newRow * newColumn];
    double min = - std::numeric_limits<double>::max();

    for (unsigned int i = 0; i < currentRow; i++)
        for (unsigned int j = 0; j < currentColumn; j++)
            temp[i * currentColumn + j] = min;

    for (unsigned int i = 0; i < currentRow; i++)
        for (unsigned int j = 0; j < currentColumn; j++)
            temp[i * currentColumn + j] = value[i][j];

    maxValue.clear();
    for (unsigned int i = 0; i < newRow; i++)
        maxValue.push_back(std::vector<bool>(newColumn, false));

    currentRow = newRow / maxPoolingCoreSize;
    currentColumn = newColumn / maxPoolingCoreSize;

    value.clear();
    for (unsigned int i = 0; i < currentRow; i++)
        value.push_back(std::vector<double>(currentColumn));

    unsigned int l = 0, m = 0;
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

            maxValue[maxI][maxJ] = true;
            value[m][l] = max;
            l++;
        }
        l = 0;
        m++;
    }

    delete [] temp;
}

void CoreInteractor::revConvolution(std::vector<std::vector<double>> delta) {
    if (isMaxPoolingEnabled)
        delta = maxPoolingRev(delta);

    unsigned int deltaCore = coreSize - 1;
    unsigned int currentRow = delta.size();
    unsigned int currentColumn = delta[0].size();
    unsigned int newRow = deltaCore * 2 + currentRow;
    unsigned int newColumn = deltaCore * 2 + currentColumn;

    std::vector<std::vector<double>> temp;
    for (unsigned int i = 0; i < newRow; i++)
        temp.push_back(std::vector<double>(newColumn, 0));

    for (unsigned int i = 0; i < currentRow; i++)
        for (unsigned int j = 0; j < currentColumn; j++)
            temp[i + deltaCore][j + deltaCore] = delta[i][j];

    this->delta = convolution(temp, weight); //rotate weight to 180
}

std::vector<std::vector<double>> CoreInteractor::maxPoolingRev(std::vector<std::vector<double>> delta) {
    unsigned int newRow = delta.size() * maxPoolingCoreSize;
    unsigned int newColumn = delta[0].size() * maxPoolingCoreSize;

    std::vector<std::vector<double>> temp(delta);
    delta.clear();
    for (unsigned int i = 0; i < newRow; i++)
        delta.push_back(std::vector<double>(newColumn, 0));

    unsigned int k = 0, p = 0;
    for (unsigned int i = 0; i < newRow; i++) {
        for (unsigned int j = 0; j < newColumn; j++) {
            if (!maxValue[i][j])
                continue;

            delta[i][j] = temp[k][p];
            p++;

            if (p == temp[0].size()) {
                p = 0;
                k++;
            }
        }
    }

    return delta;
}

CoreModel CoreInteractor::getModel() {
    CoreModel model(id);

    model.setType(type);
    model.setWeight(weight);
    model.setCoreSize(coreSize);
    model.setInputNeuronID(inputListener->getID());
    model.setOutputNeuronID(outputListener->getID());
    model.setIsMaxPoolingEnable(isMaxPoolingEnabled);
    model.setMaxPoolingCoreSize(maxPoolingCoreSize);

    return model;
}

void CoreInteractor::updateFromModel(CoreModel model) {
    weight.clear();
    weight = model.getWeight();
    coreSize = model.getCoreSize();
    isMaxPoolingEnabled = model.getIsMaxPoolingEnable();
    maxPoolingCoreSize = model.getMaxPoolingCoreSize();
}

std::vector<std::vector<double>> CoreInteractor::getValue() {
    return value;
}

std::vector<std::vector<double>>CoreInteractor::getDelta() {
    return delta;
}

void CoreInteractor::sendDelta(std::vector<std::vector<double>> delta) {
    revConvolution(delta);
    inputListener->onDeltaValueChanged();
}

void CoreInteractor::setView(SinapsPresentorListener *listener) {
    view = listener;
}

void CoreInteractor::deleteSinaps() {
    removeSinaps();
}
