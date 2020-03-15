#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QGraphicsView>

class MainWindowInterface;

class GraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicView(MainWindowInterface *view, QGraphicsScene *scene);

protected:
    void wheelEvent(QWheelEvent *e) override;

private:
    MainWindowInterface *view;
};

#endif // GRAPHICVIEW_H
