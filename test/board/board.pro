! include (../test_common.pri)


QT += testlib
QT += core concurrent
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TARGET = board_test
TEMPLATE = app



SOURCES += \
    BridgeCrossingBoardTest.cpp

# Library linking


unix|win32: LIBS += -L$$OUT_PWD/../../logic/ -llogic

INCLUDEPATH += $$PWD/../../logic
DEPENDPATH += $$PWD/../../logic

unix|win32: LIBS += -L$$OUT_PWD/../../access/ -laccess

INCLUDEPATH += $$PWD/../../access
DEPENDPATH += $$PWD/../../access

unix|win32: LIBS += -L$$OUT_PWD/../../common/ -lcommon

INCLUDEPATH += $$PWD/../../common
DEPENDPATH += $$PWD/../../common
