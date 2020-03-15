#ifndef MAINWINDOWINTERFACE_H
#define MAINWINDOWINTERFACE_H

class QAction;

class MainWindowInterface
{
public:
    virtual QAction *getAction(int type) = 0;
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;
};

#endif // MAINWINDOWINTERFACE_H
