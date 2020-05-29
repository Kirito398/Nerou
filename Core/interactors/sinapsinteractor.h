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
    virtual void updateSinaps(double learningRange, double alpha, double b) = 0;
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
    double optimize(double grad, double learningRange, double alpha, double prevDelta, double b, double &prevS);

protected:
    SinapsListener *inputListener;
    SinapsListener *outputListener;
    unsigned long id;
    SinapsType type;

private:
    double gradient(double grad, double learningRange);
    double momentum(double grad, double learningRange, double alpha, double prevDelta);
    double rmsProp(double grad, double learningRange, double alpha, double prevDelta, double b, double &prevS);
    double adam(double grad, double learningRange, double alpha, double prevDelta, double b, double &prevS);

private:
    MainInteractorInterface *interactor;
    unsigned long iterationNumber;
};

#endif // SINAPSINTERACTOR_H
