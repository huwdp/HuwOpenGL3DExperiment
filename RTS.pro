TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lGLEW -lSDL2 -std=c++11 -lGLU

SOURCES += \
        main.cpp \
    GameEngine/gameengine.cpp \
    Assets/tree.cpp \
    Assets/coal.cpp \
    Assets/gold.cpp \
    GameEngine/gamestate.cpp \
    GameEngine/player.cpp \
    GameEngine/computer.cpp \
    GameEngine/human.cpp \
    Assets/drawable.cpp \
    GameEngine/coord.cpp

HEADERS += \
    GameEngine/gameengine.h \
    Assets/tree.h \
    Assets/coal.h \
    Assets/gold.h \
    GameEngine/gamestate.h \
    GameEngine/player.h \
    GameEngine/computer.h \
    GameEngine/human.h \
    Assets/drawable.h \
    GameEngine/coord.h
