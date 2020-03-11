#ifndef PERCEPTRONPRESENTORLISTENER_H
#define PERCEPTRONPRESENTORLISTENER_H


class PerceptronPresentorListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual ~PerceptronPresentorListener() = default;
};

#endif // PERCEPTRONPRESENTORLISTENER_H
