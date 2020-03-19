#ifndef SINAPSINTERACTOR_H
#define SINAPSINTERACTOR_H

class SinapsListener;
class MainInteractorInterface;

class SinapsInteractor
{
public:
    enum SinapsType {Weigth, Core};

public:
    SinapsInteractor(SinapsListener *inputListener, SinapsListener *outputListener, SinapsType type);
    virtual void init() = 0;
    virtual void updateSinaps() = 0;
    virtual ~SinapsInteractor();
    SinapsType getType();
    SinapsListener *getInputNeuron();
    SinapsListener *getOutputNeuron();
    void setInteractor(MainInteractorInterface *interface);
    void setID(unsigned long id);
    unsigned long getID() const;
    void removeSinaps();

protected:
    double random();

protected:
    SinapsListener *inputListener;
    SinapsListener *outputListener;

private:
    SinapsType type;
    MainInteractorInterface *interactor;
    unsigned long id;
};

#endif // SINAPSINTERACTOR_H
