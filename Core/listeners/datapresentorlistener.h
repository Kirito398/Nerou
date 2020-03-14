#ifndef DATAPRESENTORLISTENER_H
#define DATAPRESENTORLISTENER_H

#include <string>

class DataPresentorListener
{
public:
    virtual ~DataPresentorListener() = default;
    virtual void updatePosition(double x, double y) = 0;
    virtual void setImage(std::string path) = 0;
};

#endif // DATAPRESENTORLISTENER_H
