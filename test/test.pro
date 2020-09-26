! include(../common.pri)

TEMPLATE = subdirs
TARGET = test

SUBDIRS += board \
	   player


unix|win32: LIBS += -L$$OUT_PWD/../logic/ -llogic

INCLUDEPATH += $$PWD/../logic
DEPENDPATH += $$PWD/../logic


unix|win32: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
