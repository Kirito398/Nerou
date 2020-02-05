#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <models/moveitem.h>
#include <interactors/maininteractor.h>

class PaintScene : public QGraphicsScene
{
public:
    PaintScene(QObject *parent = 0);
    ~PaintScene();

private:
    MainInteractor* interactor;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PAINTSCENE_H
