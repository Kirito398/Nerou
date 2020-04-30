#ifndef PERCEPTRONVIEWLISTENER_H
#define PERCEPTRONVIEWLISTENER_H

class QString;

class PerceptronViewListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual void setActive(bool enable) = 0;
    virtual void setOutValue(QString value) = 0;
    virtual void onActivateFunctionTypeChanged(int type) = 0;
    virtual int getActivateFunctionType() = 0;
};

#endif // PERCEPTRONVIEWLISTENER_H
