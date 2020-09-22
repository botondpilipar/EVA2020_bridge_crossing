! include(../common.pri)

TEMPLATE = lib
TARGET = logic

INCLUDEPATH += include

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
