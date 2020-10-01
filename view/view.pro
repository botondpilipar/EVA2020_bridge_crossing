!include(../common.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BridgeCrossingViewManager.cpp \
    SettingsDialog.cpp \
    main.cpp

HEADERS += \
    BridgeCrossingViewManager.h \
    SettingsDialog.h

FORMS += \
    bridgecrossingviewmanager.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$OUT_PWD/../logic/ -llogic

INCLUDEPATH += $$PWD/../logic
DEPENDPATH += $$PWD/../logic


unix|win32: LIBS += -L$$OUT_PWD/../access/ -laccess

INCLUDEPATH += $$PWD/../access
DEPENDPATH += $$PWD/../access


unix|win32: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
