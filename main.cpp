// Headerphile.com OpenGL Tutorial part 1
// A Hello World in the world of OpenGL ( creating a simple windonw and setting background color )
// Source code is an C++ adaption / simplicication of : https://www.opengl.org/wiki/Tutorial1:_Creating_a_Cross_Platform_OpenGL_3.2_Context_in_SDL_(C_/_SDL)
// Compile : clang++ main.cpp -lGL -lSDL2 -std=c++11 -o Test

// C++ Headers
#include <string>
#include <iostream>

// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// SDL2 Headers
#include <SDL2/SDL.h>

#include <memory>

#include "GameEngine/gameengine.h"


int main()
{
    std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();

    if (!gameEngine->init())
    {
        return -1;
    }

    gameEngine->run();

    gameEngine->cleanUp();

    return 0;
}
