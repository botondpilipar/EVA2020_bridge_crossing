! include(../common.pri)

QT += core

TEMPLATE = lib
TARGET = logic
DEFINES = logic_library
CONFIG += create_prl
CONFIG += link_prl
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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../access/release/ -lACCESS
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../access/debug/ -lACCESS
else:unix: LIBS += -L$$OUT_PWD/../access/ -lACCESS

INCLUDEPATH += $$PWD/../access
DEPENDPATH += $$PWD/../access

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon
#else:unix: LIBS += -L$$OUT_PWD/../common/ -lcommon

#INCLUDEPATH += $$PWD/../common
#DEPENDPATH += $$PWD/../common
