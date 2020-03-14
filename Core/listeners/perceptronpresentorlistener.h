#ifndef PERCEPTRONPRESENTORLISTENER_H
#define PERCEPTRONPRESENTORLISTENER_H


class PerceptronPresentorListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual ~PerceptronPresentorListener() = default;
    virtual void setOutValue(double value) = 0;
    virtual void setActive(bool enable) = 0;
};

#endif // PERCEPTRONPRESENTORLISTENER_H
