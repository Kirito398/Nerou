#ifndef PAINTSCENEINTERFACE_H
#define PAINTSCENEINTERFACE_H

#include <QList>

class QPointF;
class QGraphicsItem;
class QAction;
class QStringList;

enum ActionType {Delete, AddOutputNeurons, MakeOutputNeuron, MakeForwardNeuron};

class PaintSceneInterface
{
public:
    virtual void updateScene() = 0;
    virtual void updateItem(QGraphicsItem *item) = 0;
    virtual void moveSelectedItem(QPointF delta) = 0;
    virtual void deleteItem(QGraphicsItem *item) = 0;
    virtual QAction *getAction(int type) = 0;
    virtual void clearSelectedItem() = 0;
    virtual QStringList getOutputsNeuronsList() = 0;
    virtual QList<QGraphicsItem *> getSelectedMovingView() = 0;
};

#endif // PAINTSCENEINTERFACE_H
