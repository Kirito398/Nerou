#ifndef PAINTSCENEINTERFACE_H
#define PAINTSCENEINTERFACE_H

class QPointF;
class QGraphicsItem;
class QAction;

class PaintSceneInterface
{
public:
    virtual void updateScene() = 0;
    virtual void moveSelectedItem(QPointF delta) = 0;
    virtual void deleteItem(QGraphicsItem *item) = 0;
    virtual QAction *getDeleteAction() = 0;
    virtual void clearSelectedItem() = 0;
};

#endif // PAINTSCENEINTERFACE_H
