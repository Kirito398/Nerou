#ifndef DATAINTERACTORINTERFACE_H
#define DATAINTERACTORINTERFACE_H


class DataInteractorInterface
{
public:
    virtual unsigned long getClassNumber() = 0;
    virtual unsigned long getTrainingIterationNumber() = 0;
    virtual void start(unsigned long classNumber, unsigned long iterationNumber) = 0;
    virtual double getLoss() = 0;
    virtual unsigned int getAnswer() = 0;
};

#endif // DATAINTERACTORINTERFACE_H
