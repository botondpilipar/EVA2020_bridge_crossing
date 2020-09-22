QT += testlib
QT -= gui

! include (../common.pri)
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += link_prl
TARGET = TEST
TEMPLATE = app

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../access/release/ -lACCESS
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../access/debug/ -lACCESS
else:unix: LIBS += -L$$OUT_PWD/../access/ -lACCESS

INCLUDEPATH += $$PWD/../access
DEPENDPATH += $$PWD/../access

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logic/release/ -llogic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logic/debug/ -llogic
else:unix: LIBS += -L$$OUT_PWD/../logic/ -llogic

INCLUDEPATH += $$PWD/../logic
DEPENDPATH += $$PWD/../logic


SOURCES += \
    BridgeCrossingPlayerTest.cpp
