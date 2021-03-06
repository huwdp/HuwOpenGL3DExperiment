#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <memory>

#include "GameEngine/gameengine.h"

int main(int argc, char** argv)
{
    GameEngine::init();
    GameEngine::run(argc, argv);
    GameEngine::cleanUp();
    return 0;
}
