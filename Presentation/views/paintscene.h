#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

#include <models/moveitem.h>
#include <interactors/maininteractor.h>
#include <interfaces/PaintSceneInterface.h>
#include <models/arrowitem.h>

class PaintScene : public QGraphicsScene, public PaintSceneInterface
{
public:
    PaintScene(QObject *parent = nullptr);
    enum Mode {Items, Arrows};
    void setMode(Mode mode);

private:
    MainInteractor* interactor;
    ArrowItem* currentArrow;
    Mode mode = Items;
    QGraphicsLineItem *line;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void updateScene() override;
};

#endif // PAINTSCENE_H
