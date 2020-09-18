WARNINGS += -Wall
CONFIG += c++17
CONFIG += warn_on

top_srcdir=$$PWD
top_builddir=$$shadowed($$PWD)

INCLUDEPATH += $$top_srcdir/utility/include
INCLUDEPATH += $$top_srcdir/access/include
PRECOMPILED_HEADER = $$top_srcdir/utility/include/common_pch.h

HEADERS += \
    $$PWD/common/include/SingletonFactory.hpp
