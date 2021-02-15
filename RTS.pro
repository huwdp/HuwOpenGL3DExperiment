TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lSDL2 -std=c++11 -lGLU -lGL -lGLU -lglut

SOURCES += \
    GameEngine/ai/airunner.cpp \
    GameEngine/ai/aistateobj.cpp \
    GameEngine/ai/enemynpc.cpp \
    GameEngine/ai/gridnode.cpp \
    GameEngine/ai/pathfinder.cpp \
    GameEngine/commandrunner.cpp \
    GameEngine/objects/cone.cpp \
    GameEngine/objects/cube.cpp \
    GameEngine/objects/floor.cpp \
    GameEngine/objects/npc.cpp \
    GameEngine/objects/object.cpp \
    GameEngine/objects/skybox.cpp \
    GameEngine/objects/sphere.cpp \
    GameEngine/objects/texturedcube.cpp \
    GameEngine/texture.cpp \
        main.cpp \
    GameEngine/gameengine.cpp

HEADERS += \
    GameEngine/ai/ainpc.h \
    GameEngine/ai/airunner.h \
    GameEngine/ai/aistateobj.h \
    GameEngine/ai/enemynpc.h \
    GameEngine/ai/enums.h \
    GameEngine/ai/gridnode.h \
    GameEngine/ai/pathfinder.h \
    GameEngine/commandrunner.h \
    GameEngine/gameengine.h \
    GameEngine/objects/cone.h \
    GameEngine/objects/cube.h \
    GameEngine/objects/floor.h \
    GameEngine/objects/npc.h \
    GameEngine/objects/object.h \
    GameEngine/objects/skybox.h \
    GameEngine/objects/sphere.h \
    GameEngine/objects/texturedcube.h \
    GameEngine/texture.h \
    defines.h

DISTFILES += \
    LICENSE \
    README.md \
    main.txt \
    main2.txt \
    main4.txt
