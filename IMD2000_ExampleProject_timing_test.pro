
#build with Qt 5.14.2 - MinGW 7.3.0

QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

win32: LIBS += -L$$PWD/ -lIMD2000_radarAPI
unix: LIBS += -L$$PWD/ -lIMD2000_radarAPI

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/IMD2000_radarAPI.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/libIMD2000_radarAPI.a

HEADERS += \
        IMD2000_radarAPI_if.h \
        IMD2000_radarAPI_structs.h \
        IMD2000_radarAPI_enums.h \
        IMD2000_radarAPI_basicTypes.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
