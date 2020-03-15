#include "graphicview.h"

#include <QWheelEvent>
#include <QtMath>

GraphicView::GraphicView(QGraphicsScene *scene) : QGraphicsView(scene) {
    zoomValue = 0;
}

void GraphicView::wheelEvent(QWheelEvent *e){
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            zoomValue += 6;
        else
            zoomValue -= 6;
        e->accept();
        setupMatrix();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

void GraphicView::setupMatrix() {
    qreal scale = qPow(qreal(2), zoomValue / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);

    setMatrix(matrix);
}
