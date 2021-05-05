#include "airunner.h"

#include "enums.h"
#include "../coord2d.h"
#include "GameEngine/gameengine.h"
#include "pathfinder.h"
#include <algorithm>
#include <time.h>
#include <chrono>

AIRunner::AIRunner()
{

}

void AIRunner::runAI(std::vector<std::shared_ptr<AINPC>> npcs,
                     std::vector<std::shared_ptr<Object>> objects,
                     int grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT],
                     float playerX,
                     float playerY)
{
    for (auto it = npcs.begin(); it != npcs.end(); it++)
    {
        auto npc = (*it);
        auto currentState = npc->topStack();
        std::time_t time = std::time(0);

        if (npc->health < 10 && currentState->state != 2) // FLEE
        {
            npc->pushToStack(std::make_shared<AIStateObj>(2, time, 10));
        }

        if (currentState->state == 0) // IDLE10SEC
        {
            // Do nothing
            if (currentState->timestamp + currentState->seconds*1000 > time)
            {
                npc->popStack();
            }
        }
        else if (currentState->state == 1) // ATTACK
        {
            if (playerX != lastPlayerGridX || playerY != lastPlayerGridY)
            {
                // Attack and follow player
                // TODO
                //npc->popStack();

                while (!npc->pathStack.empty())
                {
                    npc->pathStack.pop();
                }

                // Run pathfinder and compute path

                std::srand(std::time(0)+playerY);

                int xx = GameEngine::x3DOpenGLGridTo2dGrid(playerX);
                int yy = GameEngine::y3DOpenGLGridTo2dGrid(playerY);

                auto path = Pathfinder::generatePath(grid,
                                         GameEngine::x3DOpenGLGridTo2dGrid(npc->x),
                                         GameEngine::y3DOpenGLGridTo2dGrid(npc->z),
                                         xx,
                                         yy);

                std::reverse(std::begin(path), std::end(path));

                for (std::vector<std::shared_ptr<Coord2D>>::iterator it = path.begin(); it != path.end(); ++it)
                {
                    npc->pathStack.push((*it));
                }

                if (!npc->pathStack.empty())
                {
                    npc->pathStack.pop(); // Leave one block out so that it stays outside player
                }
            }
        }
        else if (currentState->state == 2) // FLEE
        {
            // Find a place to hide and take cover
            // TODO
            npc->popStack();





            bool isPlayerFacingNorth = false;
            bool isPlayerFacingWest = false;
            std::vector<std::shared_ptr<Object>> objectsToHideBehind;
            for (auto it = objects.begin(); it != objects.end(); ++it)
            {
                std::shared_ptr<Object> obj = (*it);
                // Things to check

                // Add obj to list if it's in front of player and obj is high enough to cover npc

                // Add obj to list if it's in behind player


                if (isPlayerFacingNorth && obj->x < playerX)
                {
                    if (obj->height > 1) // Replace 1 with npc height
                    {
                        objectsToHideBehind.push_back(obj);
                    }
                }
                if (!isPlayerFacingNorth && obj->x > playerX)
                {
                    objectsToHideBehind.push_back(obj);
                }

                if (isPlayerFacingWest && obj->y < playerY)
                {
                    if (obj->height > 1) // Replace 1 with npc height
                    {
                        objectsToHideBehind.push_back(obj);
                    }
                }
                if (!isPlayerFacingWest && obj->y > playerY)
                {
                    objectsToHideBehind.push_back(obj);
                }
            }

            /*
            // Choose best or random object to hide NPC behind
            if (objectsToHideBehind.size() > 0)
            {
                auto destination = objectsToHideBehind.front();

                int xSide = 1;
                int ySide = 1;

                if (isPlayerFacingNorth)
                {
                    xSide = -1;
                }
                if (isPlayerFacingWest)
                {
                    ySide = -1;
                }

                auto path = Pathfinder::generatePath(grid,
                                         GameEngine::x3DOpenGLGridTo2dGrid(npc->x),
                                         GameEngine::y3DOpenGLGridTo2dGrid(npc->z),
                                         GameEngine::x3DOpenGLGridTo2dGrid(destination->x)+1,
                                         GameEngine::y3DOpenGLGridTo2dGrid(destination->y)+1);

                std::reverse(std::begin(path), std::end(path));
                npc->destGridX = xx;
                npc->destGridY = yy;
            }*/
        }
        else if (currentState->state == 3) // PARTOL
        {
            if (npc->pathStack.empty())
            {
                // Randomly walk around slowly
                // TODO
                //npc->popStack();

                while (!npc->pathStack.empty())
                {
                    npc->pathStack.pop();
                }

                // Run pathfinder and compute path

                const int xUpper = GRID_MAP_WIDTH-1;
                const int xLower = 0;

                const int yUpper = GRID_MAP_HEIGHT-1;
                const int yLower = 0;

                auto seed = std::chrono::system_clock::now().time_since_epoch().count();



                std::srand(seed+playerY);




                int xx = (rand() % (xUpper - xLower + 1)) + xLower;

                seed = std::chrono::system_clock::now().time_since_epoch().count();


                std::srand(seed);
                int yy = (rand() % (yUpper - yLower + 1)) + yLower;


                auto path = Pathfinder::generatePath(grid,
                                         GameEngine::x3DOpenGLGridTo2dGrid(npc->x),
                                         GameEngine::y3DOpenGLGridTo2dGrid(npc->z),
                                         xx,
                                         yy);

                std::reverse(std::begin(path), std::end(path));

                npc->destGridX = xx;
                npc->destGridY = yy;

                for (std::vector<std::shared_ptr<Coord2D>>::iterator it = path.begin(); it != path.end(); ++it)
                {
                    npc->pathStack.push((*it));
                }
            }
        }

        // Heal
        if (npc->health < 100 && npc->lastTimeHealed < time-10)
        {
            npc->health++;
            npc->lastTimeHealed = time;
        }

        if (npc->pathStack.size() > 0 && npc->lastMoved < std::time(0)*1000-10) //100 milliseconds
        {
            auto latestGridOnPath = npc->pathStack.top();
            npc->pathStack.pop();

            npc->x = GameEngine::x2DGridTo3DOpenGLGrid(latestGridOnPath->x);
            npc->z = GameEngine::y2DGridTo3DOpenGLGrid(latestGridOnPath->y);
            npc->lastMoved = std::time(0)*1000;
        }
    }

    // Cache player's x & y grid positions
    lastPlayerGridX = playerX;
    lastPlayerGridY = playerY;
}

int AIRunner::lastPlayerGridX = 0;
int AIRunner::lastPlayerGridY = 0;
