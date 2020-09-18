! include(../common.pri)

TEMPLATE = lib
TARGET = ACCESS
INCLUDEPATH += include
HEADERS += include/ISerializable.h \
    include/IDataInitializable.hpp \
    include/IDeserializable.h \
    include/StreamSerializationSource.h \
    include/StreamSerializationTarget.h
            include/ISerializationSource.h
            include/ISerializationTarget.h
            include/SingletonFactory.h

SOURCES += \
    src/StreamSerializationSource.cpp \
    src/StreamSerializationTarget.cpp
