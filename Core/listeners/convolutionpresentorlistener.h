#ifndef CONVOLUTIONPRESENTORLISTENER_H
#define CONVOLUTIONPRESENTORLISTENER_H

#include <vector>

class ConvolutionPresentorListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual ~ConvolutionPresentorListener() = default;
    virtual void setActive(bool enable) = 0;
    virtual void setOutValue(std::vector<std::vector<double>> value) = 0;
};

#endif // CONVOLUTIONPRESENTORLISTENER_H
