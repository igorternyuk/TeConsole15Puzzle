QT += core
QT -= gui

CONFIG += c++11

TARGET = Puzzle15Console
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    puzzle15model.cpp \
    view.cpp \
    controller.cpp

HEADERS += \
    puzzle15model.h \
    defines.h \
    view.h \
    controller.h
