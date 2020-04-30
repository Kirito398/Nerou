#QT       += core gui

qtHaveModule(opengl): QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += charts

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogs/addoutputneuronsdialog.cpp \
    dialogs/convolutionparametersdialog.cpp \
    dialogs/dataaddsetdialog.cpp \
    dialogs/dataparametersdialog.cpp \
    dialogs/datasetsdialog.cpp \
    dialogs/parametersdialog.cpp \
    dialogs/perceptronparametersdialog.cpp \
    dialogs/progresstrainingdialog.cpp \
    dialogs/progresstrainingplotsdialog.cpp \
    main.cpp \
    models/selectoritem.cpp \
    presenters/arrowpresentor.cpp \
    presenters/convolutionpresentor.cpp \
    presenters/datapresentor.cpp \
    presenters/perceptronpresentor.cpp \
    views/arrowview.cpp \
    views/convolutionview.cpp \
    views/dataview.cpp \
    views/graphicview.cpp \
    views/mainwindow.cpp \
    views/movingview.cpp \
    views/paintscene.cpp \
    views/perceptronview.cpp

HEADERS += \
    dialogs/addoutputneuronsdialog.h \
    dialogs/convolutionparametersdialog.h \
    dialogs/dataaddsetdialog.h \
    dialogs/dataparametersdialog.h \
    dialogs/datasetsdialog.h \
    dialogs/parametersdialog.h \
    dialogs/perceptronparametersdialog.h \
    dialogs/progresstrainingdialog.h \
    dialogs/progresstrainingplotsdialog.h \
    interfaces/PaintSceneInterface.h \
    interfaces/arrowinterface.h \
    interfaces/mainwindowinterface.h \
    interfaces/movingviewinterface.h \
    listeners/arrowviewlistener.h \
    listeners/convolutionviewlistener.h \
    listeners/dataviewlistener.h \
    listeners/perceptronviewlistener.h \
    models/selectoritem.h \
    presenters/arrowpresentor.h \
    presenters/convolutionpresentor.h \
    presenters/datapresentor.h \
    presenters/perceptronpresentor.h \
    views/arrowview.h \
    views/convolutionview.h \
    views/dataview.h \
    views/graphicview.h \
    views/mainwindow.h \
    views/movingview.h \
    views/paintscene.h \
    views/perceptronview.h

RESOURCES += res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Data/release/ -lData
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Data/debug/ -lData
else:unix: LIBS += -L$$OUT_PWD/../Data/ -lData

INCLUDEPATH += $$PWD/../Data
DEPENDPATH += $$PWD/../Data
