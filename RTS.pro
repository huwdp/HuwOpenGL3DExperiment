TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lSDL2 -std=c++11 -lGLU -lGL -lGLU -lglut

SOURCES += \
    GameEngine/ai/gridnode.cpp \
    GameEngine/npc.cpp \
    GameEngine/objects/cube.cpp \
    GameEngine/objects/floor.cpp \
    GameEngine/objects/object.cpp \
    GameEngine/objects/texturedcube.cpp \
    GameEngine/texture.cpp \
        main.cpp \
    GameEngine/gameengine.cpp \
    GameEngine/player.cpp \
    GameEngine/coord.cpp

HEADERS += \
    GameEngine/ai/gridnode.h \
    GameEngine/gameengine.h \
    GameEngine/npc.h \
    GameEngine/objects/cube.h \
    GameEngine/objects/floor.h \
    GameEngine/objects/object.h \
    GameEngine/objects/texturedcube.h \
    GameEngine/player.h \
    GameEngine/coord.h \
    GameEngine/texture.h

DISTFILES += \
    LICENSE \
    README.md \
    main.txt \
    main2.txt \
    main4.txt
