TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lSDL2 -std=c++11 -lGLU -lGL -lGLU -lglut

SOURCES += \
        main.cpp \
    GameEngine/gameengine.cpp \
    GameEngine/player.cpp \
    GameEngine/coord.cpp

HEADERS += \
    GameEngine/gameengine.h \
    GameEngine/player.h \
    GameEngine/coord.h

DISTFILES += \
    LICENSE \
    README.md \
    main.txt \
    main2.txt \
    main4.txt
