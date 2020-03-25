#ifndef CONVOLUTIONVIEWLISTENER_H
#define CONVOLUTIONVIEWLISTENER_H


class ConvolutionViewListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual void setActive(bool enable) = 0;
};

#endif // CONVOLUTIONVIEWLISTENER_H
