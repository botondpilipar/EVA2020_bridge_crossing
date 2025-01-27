WARNINGS += -Wall
CONFIG += c++17
CONFIG += warn_on
QMAKE_CXXFLAGS += -v
QMAKE_CXXFLAGS += -std=c++1z

top_srcdir=$$PWD
top_builddir=$$shadowed($$PWD)

INCLUDEPATH += $$top_srcdir/utility/include
INCLUDEPATH += $$top_srcdir/access/include
INCLUDEPATH += $$top_srcdir/common/include
INCLUDEPATH += $$top_srcdir/logic/include
PRECOMPILED_HEADER = $$top_srcdir/utility/include/common_pch.h

RESOURCES += \
    $$PWD/res.qrc
