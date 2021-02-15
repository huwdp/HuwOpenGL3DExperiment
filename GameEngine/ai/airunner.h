#ifndef AIRUNNER_H
#define AIRUNNER_H

#include <vector>
#include <memory>
#include "ainpc.h"
#include "defines.h"

class AIRunner
{
private:
   static int lastPlayerGridX;
   static int lastPlayerGridY;
public:
    AIRunner();
    static void popOffStackIfPossible(std::shared_ptr<AINPC> npc);
    static void runAI(std::vector<std::shared_ptr<AINPC>> npcs,
                         int grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT],
                         float playerX,
                         float playerY);
};

#endif // AIRUNNER_H
