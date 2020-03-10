#ifndef ARROWINTERFACE_H
#define ARROWINTERFACE_H

class MovingViewInterface;

class ArrowInterface
{
public:
    virtual MovingViewInterface *getStartView() = 0;
    virtual MovingViewInterface *getEndView() = 0;
    virtual void updatePosition() = 0;
    virtual ~ArrowInterface() = default;
};

#endif // ARROWINTERFACE_H
