QT -= gui qt

TEMPLATE = lib
DEFINES += CORE_LIBRARY

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
    interactors/convolutioninteractor.cpp \
    interactors/coreinteractor.cpp \
    interactors/datainteractor.cpp \
    interactors/maininteractor.cpp \
    interactors/neuroninteractor.cpp \
    interactors/perceptroninteractor.cpp \
    interactors/sinapsinteractor.cpp \
    interactors/tabledatainteractor.cpp \
    interactors/weightinteractor.cpp \
    models/classmodel.cpp \
    models/convolutionmodel.cpp \
    models/coremodel.cpp \
    models/datamodel.cpp \
    models/perceptronmodel.cpp \
    models/weightmodel.cpp

HEADERS += \
    Core_global.h \
    enums/lossfunctiontypeenum.h \
    interactors/convolutioninteractor.h \
    interactors/coreinteractor.h \
    interactors/datainteractor.h \
    interactors/maininteractor.h \
    interactors/neuroninteractor.h \
    interactors/perceptroninteractor.h \
    interactors/sinapsinteractor.h \
    interactors/tabledatainteractor.h \
    interactors/weightinteractor.h \
    interfaces/coreinterface.h \
    interfaces/maininteractorinterface.h \
    interfaces/repositoryinterface.h \
    interfaces/weightinterface.h \
    listeners/SinapsListener.h \
    listeners/arrowinteractorlistener.h \
    listeners/convolutioninteractorlistener.h \
    listeners/convolutionpresentorlistener.h \
    listeners/datainteractorlistener.h \
    listeners/datapresentorlistener.h \
    listeners/mainpresentorlistener.h \
    listeners/perceptroninteractorlistener.h \
    listeners/perceptronpresentorlistener.h \
    listeners/sinapspresentorlistener.h \
    listeners/tabledatainteractorlistener.h \
    listeners/tabledatapresentorlistener.h \
    models/classmodel.h \
    models/convolutionmodel.h \
    models/coremodel.h \
    models/datamodel.h \
    models/perceptronmodel.h \
    models/weightmodel.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
