#ifndef TABLEDATAINTERACTORLISTENER_H
#define TABLEDATAINTERACTORLISTENER_H

#include <vector>
#include <string>

#include "enums/lossfunctiontypeenum.h"

class TableDataModel;
class TableDataPresentorListener;
class RepositoryInterface;

class TableDataInteractorListener
{
public:
    virtual void setView(TableDataPresentorListener *listener) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void deleteNeuron() = 0;
    virtual unsigned long getID() = 0;
    virtual void setLossFunctionType(LossFunctionType type) = 0;
    virtual LossFunctionType getLossFunctionType() = 0;
    virtual void setActivateFunctionType(int type) = 0;
    virtual int getActivateFunctiontype() = 0;
    virtual std::vector<std::vector<std::string>> loadTableValue(std::string path) = 0;
    virtual std::string getDataSetMainPath() = 0;
    virtual void setDataSetMainPath(std::string path) = 0;
    virtual void addTrainingInputSet(std::vector<std::string> set) = 0;
    virtual void addTrainingTargetSet(std::vector<std::string> set) = 0;
    virtual void addTestingInputSet(std::vector<std::string> set) = 0;
    virtual void addTestingTargetSet(std::vector<std::string> set) = 0;
    virtual void setTargetTitles(std::vector<std::string> titles) = 0;
    virtual void setInputsTitles(std::vector<std::string> titles) = 0;
    virtual std::vector<std::string> getTargetTitles() = 0;
    virtual std::vector<std::string> getInputsTitles() = 0;
    virtual void clearDataSet() = 0;
};

#endif // TABLEDATAINTERACTORLISTENER_H
