QT += core gui widgets testlib

CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++11

TEMPLATE = app

TARGET = horizontal_movement_test

SOURCES += \
    step_definitions/horizontal_movement_steps.cpp \
    ../chessboard.cpp \
    ../chesspiece.cpp \
    ../game.cpp

HEADERS += \
    ../chessboard.h \
    ../chesspiece.h \
    ../game.h \
    ../addition.h \
    step_definitions/test_context.h

FORMS += \
    ../chessboard.ui

INCLUDEPATH += .. \
    step_definitions

RESOURCES += ../data.qrc
