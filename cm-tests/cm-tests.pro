QT += testlib
QT -= gui

TARGET = client-tests
TEMPLATE = app

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++14

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

INCLUDEPATH += source

SOURCES += source/models/client-tests.cpp

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lcm-lib

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui
