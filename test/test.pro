QT += testlib
QT += core
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

unix|win32: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

unix|win32: LIBS += -L$$OUT_PWD/../access/ -laccess

INCLUDEPATH += $$PWD/../access
DEPENDPATH += $$PWD/../access
