! include(../common.pri)

QT += core

TEMPLATE = lib
TARGET = logic
DEFINES = LOGIC

CONFIG += staticlib

unix|win32: LIBS += -L$$OUT_PWD/../access/ -laccess

INCLUDEPATH += $$PWD/../access
DEPENDPATH += $$PWD/../access

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../access/access.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../access/libaccess.a

unix|win32: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../common/common.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../common/libcommon.a

HEADERS += \
    include/BridgeCrossingBoard.h \
    include/BridgeCrossingBoardData.h \
    include/BridgeCrossingPlayer.h \
    include/BridgeCrossingPlayerData.h \
    include/BridgeCrossingSettings.h \
    include/GameLogicTypes.h \
    include/IGameActor.hpp \
    include/IGameBoard.h \
    include/IGameControlUnit.h \
    include/IMovableObject.hpp \
    include/ISettingsChangedObserver.h

SOURCES += \
    src/BridgeCrossingBoard.cpp \
    src/BridgeCrossingBoardData.cpp \
    src/BridgeCrossingPlayer.cpp \
    src/BridgeCrossingPlayerData.cpp




