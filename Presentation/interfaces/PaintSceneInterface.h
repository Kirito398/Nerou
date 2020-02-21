#ifndef PAINTSCENEINTERFACE_H
#define PAINTSCENEINTERFACE_H

#include <QPointF>

class PaintSceneInterface
{
public:
    virtual void onInputCircleClicked(QPointF position) = 0;
    virtual void onOutputCircleClicked(QPointF position) = 0;
};

#endif // PAINTSCENEINTERFACE_H
