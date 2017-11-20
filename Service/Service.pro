QT       -= gui
QT += remoteobjects
CONFIG += c++11 dll

TARGET = sunstoneservice
TEMPLATE = lib

SOURCES += \
        service.cpp \
    main.cpp

HEADERS += \
        service.h

REPC_SOURCE += ../Reps/service.rep
REPC_REPLICA += RemoteReps/remoteclientserver.rep

OTHER_FILES += \
    ../Reps/service.rep \
    RemoteReps/remoteclientserver.rep
