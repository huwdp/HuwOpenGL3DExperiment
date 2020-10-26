#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "defines.h"
#include "gridnode.h"
#include <vector>
#include <memory>

class Pathfinder
{
public:
    static int pathfindingGrid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT];
    static std::vector<std::shared_ptr<GridNode>> generatePath(int grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT], int startX, int startY, int endX, int endY);
};

#endif // PATHFINDER_H
