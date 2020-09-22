! include(../common.pri)

TEMPLATE = lib
TARGET = common
DEFINES = common_library
CONFIG += create_prl

INCLUDEPATH += include
HEADERS += include/SingletonFactory.hpp \
            include/UnimplementedException.h \
            include/CachedRandomDevice.h
