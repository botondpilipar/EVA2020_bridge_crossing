! include(../common.pri)

TEMPLATE = lib
TARGET = common
DEFINES = COMMON
CONFIG += staticlib

INCLUDEPATH += include
HEADERS += include/SingletonFactory.hpp \
            include/UnimplementedException.h \
            include/CachedRandomDevice.h
