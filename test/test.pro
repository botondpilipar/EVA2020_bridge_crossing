QT += testlib
QT -= gui

! include (../common.pri)
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TARGET = test
TEMPLATE = app

# Library linking



SOURCES += \
    BridgeCrossingPlayerTest.cpp


unix|win32: LIBS += -L$$OUT_PWD/../logic/ -llogic

INCLUDEPATH += $$PWD/../logic
DEPENDPATH += $$PWD/../logic

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../logic/logic.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../logic/liblogic.a
