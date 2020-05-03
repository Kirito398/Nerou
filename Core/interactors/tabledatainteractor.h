#ifndef TABLEDATAINTERACTOR_H
#define TABLEDATAINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/tabledatainteractorlistener.h"

class TableDataInteractor : public NeuronInteractor, public TableDataInteractorListener
{
public:
    TableDataInteractor();
    void setPosition(double x, double y) override;
    void setRepository(RepositoryInterface *repository);

private:
    void removeSinaps(unsigned long sinapsID) override;
    void clean() override;
    void setView(TableDataPresentorListener *listener) override;
    void deleteNeuron() override;
    unsigned long getID() override;
    void setLossFunctionType(LossFunctionType type) override;
    LossFunctionType getLossFunctionType() override;
    void setActivateFunctionType(int type) override;
    int getActivateFunctiontype() override;
    void onInputSignalChanged() override;
    void onDeltaValueChanged() override;
    std::vector<std::vector<std::string> > loadTableValue(std::string path) override;

    TableDataPresentorListener *view;
    RepositoryInterface *repository;
    LossFunctionType lossFunctionType;
};

#endif // TABLEDATAINTERACTOR_H
