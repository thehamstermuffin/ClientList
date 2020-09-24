QT += testlib
QT -= gui

TARGET = client-tests

CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += source \
    ../cm-lib/source

TEMPLATE = app

SOURCES +=  source/models/client-tests.cpp \
    source/main.cpp \
    source/test-suite.cpp

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH #-lcm-lib # is lcm-lib needed?

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

HEADERS += \
    source/test-suite.h
