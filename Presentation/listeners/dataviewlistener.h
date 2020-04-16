#ifndef DATAVIEWLISTENER_H
#define DATAVIEWLISTENER_H

class QString;
class QStringList;

class DataViewListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual void setImage(QString path) = 0;
    virtual QStringList getOutputsNeuronsList() = 0;
    virtual bool getUseColorModeEnable() = 0;
    virtual void onUseColorModeEnableChanged(bool enable) = 0;
    virtual int getActivateFunctionType() = 0;
    virtual void onActivateFunctionTypeChanged(int type) = 0;
    virtual int getLossFunctionType() = 0;
    virtual void onLossFunctionTypeChanged(int type) = 0;
    virtual void openSetsDialog() = 0;
};

#endif // DATAVIEWLISTENER_H
