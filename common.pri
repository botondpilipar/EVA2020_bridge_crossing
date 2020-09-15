WARNINGS += -Wall
CONFIG += c++17
TEMPLATE = lib

top_srcdir=$$PWD
top_builddir=$$shadowed($$PWD)

PRECOMPILED_HEADER = $$top_srcdir/utility/common_pch.h
