QT += sql network xml
QT -= gui #not needed since its a library project

TARGET = cm-lib #name for the binary output
TEMPLATE = lib

CONFIG += c++14

DEFINES += CMLIB_LIBRARY

INCLUDEPATH += source

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

SOURCES += source/models/client.cpp \
    source/controllers/command-controller.cpp \
    source/controllers/database-controller.cpp \
    source/controllers/master-controller.cpp \
    source/data/data-decorator.cpp \
    source/data/datetime-decorator.cpp \
    source/data/entity.cpp \
    source/data/enumerator-decorator.cpp \
    source/data/int-decorator.cpp \
    source/data/string-decorator.cpp \
    source/framework/command.cpp \
    source/models/address.cpp \
    source/models/appointment.cpp \
    source/models/client-search.cpp \
    source/models/contact.cpp \
    source/networking/network-access-manager.cpp \
    source/networking/web-request.cpp \
    source/utilities/xml-helper.cpp

HEADERS += \
        source/controllers/command-controller.h \
        source/controllers/database-controller.h \
        source/controllers/i-database-controller.h \
        source/controllers/master-controller.h \
        source/controllers/navigation-controller.h \
        source/data/data-decorator.h \
        source/data/datetime-decorator.h \
        source/data/entity-collection.h \
        source/data/entity.h \
        source/data/enumerator-decorator.h \
        source/data/int-decorator.h \
        source/data/string-decorator.h \
        source/framework/command.h \
        source/models/address.h \
        source/models/appointment.h \
        source/models/client-search.h \
        source/models/client.h \
        source/cm-lib_global.h \
        source/models/contact.h \
        source/networking/i-network-access-manager.h \
        source/networking/i-web-request.h \
        source/networking/network-access-manager.h \
        source/networking/web-request.h \
        source/utilities/xml-helper.h

message(cm-lib project dir: $${PWD})

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui
message(cm-lib output dir: $${DESTDIR})
