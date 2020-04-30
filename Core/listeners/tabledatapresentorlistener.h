#ifndef TABLEDATAPRESENTORLISTENER_H
#define TABLEDATAPRESENTORLISTENER_H


class TableDataPresentorListener
{
public:
    virtual ~TableDataPresentorListener() = default;
    virtual void updatePosition(double x, double y) = 0;
};

#endif // TABLEDATAPRESENTORLISTENER_H
