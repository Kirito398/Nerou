#ifndef CONVOLUTIONPRESENTOR_H
#define CONVOLUTIONPRESENTOR_H

#include "listeners/convolutionpresentorlistener.h"

class ConvolutionViewListener;
class ConvolutionInteractorListener;

class ConvolutionPresentor : public ConvolutionPresentorListener
{
public:
    ConvolutionPresentor();
    ~ConvolutionPresentor();
    void setView(ConvolutionViewListener *listener);
    void setInteractor(ConvolutionInteractorListener *listener);
    void setPosition(double x, double y);
    unsigned long getID();

private:
    void updatePosition(double x, double y) override;
    void setActive(bool enable) override;

private:
    ConvolutionViewListener *view;
    ConvolutionInteractorListener *interactor;
};

#endif // CONVOLUTIONPRESENTOR_H
