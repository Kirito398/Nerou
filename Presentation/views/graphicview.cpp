#include "graphicview.h"

#include <QWheelEvent>

#include "interfaces/mainwindowinterface.h"

GraphicView::GraphicView(MainWindowInterface *view, QGraphicsScene *scene) : QGraphicsView(scene) {
    this->view = view;
}

void GraphicView::wheelEvent(QWheelEvent *e){
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            view->zoomIn();
        else
            view->zoomOut();
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}
