#ifndef DATAPRESENTORLISTENER_H
#define DATAPRESENTORLISTENER_H


class DataPresentorListener
{
public:
    virtual ~DataPresentorListener() = default;
    virtual void updatePosition(double x, double y) = 0;
};

#endif // DATAPRESENTORLISTENER_H
