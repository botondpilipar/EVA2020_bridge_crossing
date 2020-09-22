! include(../common.pri)

QT += core

TEMPLATE = lib
TARGET = ACCESS
DEFINES = access_library
CONFIG += create_prl

INCLUDEPATH += include
HEADERS += include/ISerializable.h \
    include/IDataInitializable.hpp \
    include/IDeserializable.h \
    include/StreamSerializationSource.h \
    include/StreamSerializationTarget.h \
            include/ISerializationSource.h \
            include/ISerializationTarget.h \
            include/DeserializationFailedException.h


SOURCES += \
    src/StreamSerializationSource.cpp \
    src/StreamSerializationTarget.cpp
