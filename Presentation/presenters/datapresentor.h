#ifndef DATAPRESENTOR_H
#define DATAPRESENTOR_H

#include <vector>

#include "listeners/datapresentorlistener.h"
#include "listeners/datainteractorlistener.h"

class QPointF;
class DataViewListener;
class RepositoryInterface;
class QStringList;
class QSize;
class QString;

class DataPresentor : public DataPresentorListener
{
public:
    DataPresentor();
    ~DataPresentor();
    void setView(DataViewListener *listener);
    void setInteractor(DataInteractorListener *listener);
    void setPosition(double x, double y);
    unsigned long getID();
    void updateParameters(QStringList trainingList, QStringList testingList, QStringList neuronsIDs);
    void getParameters(QStringList *trainingList, QStringList *testingList, QStringList *neuronsIDs);
    RepositoryInterface *getRepository();
    void setUseColorModeEnable(bool enable);
    bool getUseColorModeEnable();
    void setActivateFunctionType(int type);
    int getActivateFunctionType();
    void setLossFunctionType(LossFunctionType type);
    LossFunctionType getLossFunctionType();

private:
    void updatePosition(double x, double y) override;
    void setImage(std::string path) override;

private:
    DataViewListener *view;
    DataInteractorListener *interactor;
    RepositoryInterface *repository;
};

#endif // DATAPRESENTOR_H
