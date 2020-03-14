#ifndef DATAVIEWLISTENER_H
#define DATAVIEWLISTENER_H

class QString;

class DataViewListener
{
public:
    virtual void updatePosition(double x, double y) = 0;
    virtual void setImage(QString path) = 0;
};

#endif // DATAVIEWLISTENER_H
