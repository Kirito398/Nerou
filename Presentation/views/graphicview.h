#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QGraphicsView>

class GraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicView(QGraphicsScene *scene);

protected:
    void wheelEvent(QWheelEvent *e) override;

private:
    void setupMatrix();
    int zoomValue;
};

#endif // GRAPHICVIEW_H
