QT += testlib
QT -= gui

TARGET = client-tests

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES +=  source/models/client-tests.cpp
