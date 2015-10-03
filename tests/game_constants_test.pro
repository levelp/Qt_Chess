QT += core gui widgets testlib

CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++11

TEMPLATE = app

TARGET = game_constants_test

SOURCES += \
    step_definitions/game_constants_steps.cpp \
    ../game.cpp

HEADERS += \
    ../game.h \
    ../addition.h \
    step_definitions/test_context.h

INCLUDEPATH += .. \
    step_definitions

# Use the data resources from the main project
RESOURCES += ../data.qrc
