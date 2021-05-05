#include "commandrunner.h"

#include <sstream>

#include "ai/pathfinder.h"
#include "gameengine.h"

#include <algorithm>

std::shared_ptr<AINPC> CommandRunner::getNPCByName(std::vector<std::shared_ptr<AINPC>> npcs, std::string name)
{
    for (auto it = npcs.begin(); it != npcs.end(); it++)
    {
        std::shared_ptr<AINPC> npc = (*it);
        if (npc->name == name)
        {
            return npc;
        }
    }
    return nullptr;
}

void CommandRunner::runCommand(std::string command,
                               std::vector<std::shared_ptr<AINPC>> npcs,
                               int grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT])
{
    std::vector<std::string> tokens;
    std::stringstream check1(command);
    std::string intermediate;
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }

    if (tokens.size() == 0)
    {
        return;
    }

    if (tokens[0] == "moveTo" && tokens.size() == 4)
    {
        auto npc = CommandRunner::getNPCByName(npcs, tokens[1]);
        if (npc != nullptr)
        {
            while (!npc->pathStack.empty())
            {
                npc->pathStack.pop();
            }

            // Run pathfinder and compute path

            int xx = std::stoi(tokens[2]);
            int yy = std::stoi(tokens[3]);

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
            //npc->x = xx;
            //npc->z = yy;
        }
        else
        {
            std::cout << "Could not find object with name of \'" << tokens[1] << " \'" << std::endl;
        }

    }
    else if (tokens[0] == "pushState" && tokens.size() == 3)
    {
        std::string bob = tokens[1];
        std::shared_ptr<AINPC> npc = getNPCByName(npcs, bob);

        if (npc != nullptr)
        {
            if (tokens[2] == "idle10")
            {
                npc->pushToStack(std::make_shared<AIStateObj>(0, std::time(0)*1000, 10));
            }
            if (tokens[2] == "attack")
            {
                npc->pushToStack(std::make_shared<AIStateObj>(1, std::time(0)*1000));
            }
            if (tokens[2] == "flee")
            {
                npc->pushToStack(std::make_shared<AIStateObj>(2, std::time(0)*1000));
            }
            if (tokens[2] == "patrol")
            {
                npc->pushToStack(std::make_shared<AIStateObj>(3, std::time(0)*1000));
            }
            if (tokens[2] == "alert")
            {
                npc->pushToStack(std::make_shared<AIStateObj>(4, std::time(0)*1000));
            }
        }
        else
        {
            std::cout << "Could not find object with name of \'" << tokens[1] << " \'" << std::endl;
        }
    }
    else if (tokens[0] == ("getState") && tokens.size() == 2)
    {
        auto npc = CommandRunner::getNPCByName(npcs, tokens[1]);
        if (npc != nullptr)
        {
            std::cout << "State: " << npc->topStack()->state << std::endl;
        }
        else
        {
            std::cout << "Could not find object with name of \'" << tokens[1] << " \'" << std::endl;
        }
    }
    else if (tokens[0] == ("popState") && tokens.size() == 2)
    {
        auto npc = CommandRunner::getNPCByName(npcs, tokens[1]);
        if (npc != nullptr)
        {
            npc->popStack();

            // Also wipe path
            while (!npc->pathStack.empty())
            {
                npc->pathStack.pop();
            }

            std::cout << "Popped state off object with name of \"" << npc->name << "\"" << std::endl;
        }
        else
        {
            std::cout << "Could not find object with name of \'" << tokens[1] << " \'" << std::endl;
        }
    }
    else if (tokens[0] == "setHealth" && tokens.size() == 3)
    {
        auto npc = CommandRunner::getNPCByName(npcs, tokens[1]);
        if (npc != nullptr)
        {
            npc->health = std::stoi(tokens[2]);
            std::cout << "Set health of \"" << npc->name << "\" to " << npc->health << std::endl;
        }
        else
        {
            std::cout << "Could not find object with name of \'" << tokens[1] << " \'" << std::endl;
        }
    }
    else if (tokens[0] == "getHealth" && tokens.size() == 2)
    {
        auto npc = CommandRunner::getNPCByName(npcs, tokens[1]);
        if (npc != nullptr)
        {
            std::cout << "Health: " << npc->health << std::endl;
        }
        else
        {
            std::cout << "Could not find object with name of \'" << tokens[1] << " \'" << std::endl;
        }
    }
    else if (command == "exit")
    {
        std::exit(0);
    }
    else
    {
        std::cout << "Could not run command \"" << command << "\"" << std::endl;
    }
}
