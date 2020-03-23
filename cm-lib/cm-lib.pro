#-------------------------------------------------
#
# Project created by QtCreator 2019-08-18T21:54:51
#
#-------------------------------------------------

QT       -= gui #not needed since its a library project

TARGET = cm-lib #name for the binary output
TEMPLATE = lib

CONFIG += c++14

DEFINES += CMLIB_LIBRARY

INCLUDEPATH += source

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += source/models/client.cpp \
    source/controllers/command-controller.cpp \
    source/controllers/master-controller.cpp \
    source/data/data-decorator.cpp \
    source/data/datetime-decorator.cpp \
    source/data/enumerator-decorator.cpp \
    source/data/int-decorator.cpp \
    source/data/string-decorator.cpp \
    source/framework/command.cpp

HEADERS += \
        source/controllers/command-controller.h \
        source/controllers/master-controller.h \
        source/controllers/navigation-controller.h \
        source/data/data-decorator.h \
        source/data/datetime-decorator.h \
        source/data/enumerator-decorator.h \
        source/data/int-decorator.h \
        source/data/string-decorator.h \
        source/framework/command.h \
        source/models/client.h \
        source/cm-lib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui
