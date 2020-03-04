QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    main.cpp \
    models/arrowitem.cpp \
    models/convolutionitem.cpp \
    models/dataitem.cpp \
    models/perceptronitem.cpp \
    models/selectoritem.cpp \
    views/mainwindow.cpp \
    models/moveitem.cpp \
    views/paintscene.cpp

HEADERS += \
    interfaces/PaintSceneInterface.h \
    models/arrowitem.h \
    models/convolutionitem.h \
    models/dataitem.h \
    models/perceptronitem.h \
    models/selectoritem.h \
    views/mainwindow.h \
    models/moveitem.h \
    views/paintscene.h

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
