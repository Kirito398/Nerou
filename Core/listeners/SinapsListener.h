#ifndef SINAPSLISTENER_H
#define SINAPSLISTENER_H

class SinapsListener
{
public:
    virtual void onInputSignalChanged() = 0;
    virtual void onDeltaValueChanged() = 0;
    virtual void removeSinaps(unsigned long sinapsID) = 0;
};

#endif // SINAPSLISTENER_H