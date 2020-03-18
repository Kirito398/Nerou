#ifndef DATAPRESENTOR_H
#define DATAPRESENTOR_H

#include <vector>

#include "listeners/datapresentorlistener.h"

class QPointF;
class DataViewListener;
class DataInteractorListener;
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
    void setImageSize(QSize size);
    void updateParameters(QStringList trainingList, QStringList testingList, QStringList neuronsIDs);
    void getParameters(QStringList *trainingList, QStringList *testingList, QStringList *neuronsIDs);

private:
    void updatePosition(double x, double y) override;
    void setImage(std::string path) override;
    std::vector<std::string> getPaths(QString mainPath);

private:
    DataViewListener *view;
    DataInteractorListener *interactor;
};

#endif // DATAPRESENTOR_H
