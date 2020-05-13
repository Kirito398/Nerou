#ifndef MAINWINDOWINTERFACE_H
#define MAINWINDOWINTERFACE_H

class QAction;
class QPointF;
class QString;

class MainWindowInterface
{
public:
    virtual QAction *getAction(int type) = 0;
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;
    virtual QPointF getSceneTop() = 0;
    virtual void updateWindow() = 0;
    virtual void setProjectName(QString name) = 0;
};

#endif // MAINWINDOWINTERFACE_H
