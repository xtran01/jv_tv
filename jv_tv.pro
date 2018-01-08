TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += /usr/include/irrlicht
#INCLUDEPATH += /usr/local/include
#DEPENDPATH +=  /usr/local/lib
LIBS += -lIrrlicht -lGL -lX11 -lXxf86vm
#LIBS += -L"/usr/local/lib" -lIrrlicht

SOURCES += src/main.cpp \
         src/events.cpp \
    src/enemy.cpp \
    src/character.cpp \
    src/enemycollisionhandler.cpp \
    src/particle.cpp


HEADERS += src/events.hpp \
           src/gui_ids.h \
    src/enemy.h \
    src/character.h \
    src/enemycollisionhandler.h \
    src/particle.h




