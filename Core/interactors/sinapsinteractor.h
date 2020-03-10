#ifndef SINAPSINTERACTOR_H
#define SINAPSINTERACTOR_H

class SinapsListener;

class SinapsInteractor
{
public:
    enum SinapsType {Weigth, Core};

public:
    SinapsInteractor(SinapsListener *inputListener, SinapsListener *outputListener, SinapsType type);
    virtual void init() = 0;
    virtual ~SinapsInteractor();
    SinapsType getType();
    SinapsListener *getInputNeuron();
    SinapsListener *getOutputNeuron();

protected:
    double random();

protected:
    SinapsListener *inputListener;
    SinapsListener *outputListener;

private:
    SinapsType type;
};

#endif // SINAPSINTERACTOR_H
