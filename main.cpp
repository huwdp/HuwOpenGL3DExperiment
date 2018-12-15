#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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
