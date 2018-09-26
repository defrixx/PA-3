QT += quick widgets network multimedia sql
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    authcontroller.cpp \
    cryptocontroller.cpp \
    db_controller.cpp \
    tcpcontroller.cpp

RESOURCES += qml.qrc

INCLUDEPATH += C:\OpenSSL-Win32\includeSSL

# только в Qt под Android могут использоваться только не-versioned so-библиотеки
# Если при свобрке или запуске среда выводит <libname>.so.1.0.2 не найден, значит apk собран с
# versioned-библиотекой, где проставлена версия, значит нужно найти или собрать
# не-versioned сборку и заново подключить к приложению


android{
    LIBS += -L$$PWD/libANDRssl/ -lcrypto # libcrypto.a
}


win32-g++ {
LIBS += C:/OpenSSL-Win32/lib/libeay32.lib \
                #C:/OpenSSL-Win32/lib/ssleay32.lib \
                C:/OpenSSL-Win32/lib/ubsec.lib
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    authcontroller.h \
    cryptocontroller.h \
    db_controller.h \
    tcpcontroller.h

DISTFILES +=
