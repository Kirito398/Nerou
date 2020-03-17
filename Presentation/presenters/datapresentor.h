#ifndef DATAPRESENTOR_H
#define DATAPRESENTOR_H

#include "listeners/datapresentorlistener.h"

class QPointF;
class DataViewListener;
class DataInteractorListener;
class QStringList;
class QSize;

class DataPresentor : public DataPresentorListener
{
public:
    DataPresentor();
    ~DataPresentor();
    void setView(DataViewListener *listener);
    void setInteractor(DataInteractorListener *listener);
    void setPosition(double x, double y);
    unsigned long getID();
    void setPathsList(QStringList pathsList, bool isTrainingSet);
    void setImageSize(QSize size);

private:
    void updatePosition(double x, double y) override;
    void setImage(std::string path) override;

private:
    DataViewListener *view;
    DataInteractorListener *interactor;
};

#endif // DATAPRESENTOR_H
