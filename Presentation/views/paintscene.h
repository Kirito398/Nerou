#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <models/moveitem.h>
#include <interactors/maininteractor.h>
#include <interfaces/PaintSceneInterface.h>

class PaintScene : public QGraphicsScene, public PaintSceneInterface
{
public:
    PaintScene(QObject *parent = 0);
    ~PaintScene();

private:
    MainInteractor* interactor;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void onInputCircleClicked(QPointF position) override;
    void onOutputCircleClicked(QPointF position) override;
    void updateItemSelection();
};

#endif // PAINTSCENE_H
