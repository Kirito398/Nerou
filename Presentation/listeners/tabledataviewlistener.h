#ifndef TABLEDATAVIEWLISTENER_H
#define TABLEDATAVIEWLISTENER_H

class TableDataViewListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual bool getUseColorModeEnable() = 0;
    virtual void onUseColorModeEnableChanged(bool enable) = 0;
    virtual int getActivateFunctionType() = 0;
    virtual void onActivateFunctionTypeChanged(int type) = 0;
    virtual int getLossFunctionType() = 0;
    virtual void onLossFunctionTypeChanged(int type) = 0;
    virtual void openSetsDialog() = 0;
};

#endif // TABLEDATAVIEWLISTENER_H
