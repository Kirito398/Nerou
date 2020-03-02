#ifndef SINAPSLISTENER_H
#define SINAPSLISTENER_H

class SinapsListener
{
protected:
    virtual void onInputSignalChanged() = 0;
};

#endif // SINAPSLISTENER_H
