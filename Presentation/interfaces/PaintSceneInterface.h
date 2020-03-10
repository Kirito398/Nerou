#ifndef PAINTSCENEINTERFACE_H
#define PAINTSCENEINTERFACE_H

class QPointF;

class PaintSceneInterface
{
public:
    virtual void updateScene() = 0;
    virtual void moveSelectedItem(QPointF delta) = 0;
};

#endif // PAINTSCENEINTERFACE_H
