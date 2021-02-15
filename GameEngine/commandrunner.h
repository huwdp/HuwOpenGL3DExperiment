#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H

#include "ai/ainpc.h"

#include "gameengine.h"

#include <vector>
#include <string>

class CommandRunner
{
public:
    static std::shared_ptr<AINPC> getNPCByName(std::vector<std::shared_ptr<AINPC>> npcs, std::string name);
    static void runCommand(std::string command,
                                          std::vector<std::shared_ptr<AINPC>> npcs,
                                          int grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT]);
};

#endif // COMMANDRUNNER_H
