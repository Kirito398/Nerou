#ifndef COREINTERACTOR_H
#define COREINTERACTOR_H

#include "interfaces/coreinterface.h"
#include "listeners/arrowinteractorlistener.h"

class SinapsPresentorListener;

class CoreInteractor : public CoreInterface, public ArrowInteractorListener
{
public:
    CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener);

private:
    void init() override;
    void updateSinaps(double learningRange, double alpha) override;
    void sendSignal(double *signal, unsigned int row, unsigned int column) override;
    double *getValue() override;
    unsigned int getRow() override;
    unsigned int getColumn() override;
    void deleteSinaps() override;
    void setView(SinapsPresentorListener *listener) override;
    void deleteValue();
    void validConvolution(double *signal, unsigned int row, unsigned int column);
    void maxPooling();

private:
    SinapsPresentorListener *view;
    unsigned int coreSize, maxPoolingCoreSize, currentRow, currentColumn;
    double *value;
    double *weight;
    double *delta;
    bool isMaxPoolingEnabled;
};

#endif // COREINTERACTOR_H
