TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vector.cpp

HEADERS += \
    cstl_alloc.h \
    t.h \
    vector.h
