#ifndef CONVOLUTIONPRESENTORLISTENER_H
#define CONVOLUTIONPRESENTORLISTENER_H


class ConvolutionPresentorListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual ~ConvolutionPresentorListener() = default;
    virtual void setActive(bool enable) = 0;
};

#endif // CONVOLUTIONPRESENTORLISTENER_H
