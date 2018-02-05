TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cstl_vector.cpp \
    cstl_list.cpp

HEADERS += \
    cstl_alloc.h \
    t.h \
    cstl_iterator.h \
    cstl_type_traits.h \
    cstl_algorithm.h \
    cstl_vector.h \
    cstl_list.h
QMAKE_LFLAGS_DEBUG += /DEBUG
QMAKE_CXXFLAGS_DEBUG += /MTd
