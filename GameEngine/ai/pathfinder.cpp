#include "pathfinder.h"

#include <algorithm>
#include <queue>
#include "defines.h"

std::vector<std::shared_ptr<Coord2D>> Pathfinder::generatePath(int grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT], int startX, int startY, int endX, int endY)
{
    std::vector<std::shared_ptr<Coord2D>> path;
    std::vector<std::shared_ptr<Coord2D>> emptyPath;

    // Optimisation - If user is outside of the map
    // then don't bother to run pathfinding
    if (startX > GRID_MAP_WIDTH
            || startX < 0
            || startY > GRID_MAP_HEIGHT
            || startY < 0)
    {
        return path;
    }

    // Optimisation - No need to compute shortest path if coordinates are the same
    if (startX == endX && startY == endY)
    {
        return path;
    }

    // Clear pathfinding grid
    for (int i = 0; i < GRID_MAP_WIDTH; ++i)
    {
        for (int j = 0; j < GRID_MAP_WIDTH; ++j)
        {
            pathfindingGrid[i][j] = -1;
        }
    }

    int count = 0;
    int cost = 0;
    bool found = false;
    std::queue<std::shared_ptr<Coord2D>> gridQueue;  // Convert to priority queue for better performance
    gridQueue.push(std::make_shared<Coord2D>(startX, startY));
    pathfindingGrid[startX][startY] = cost;

    while (!gridQueue.empty() && !found && count < MAX_LIMIT)
    {
        std::shared_ptr<Coord2D> node2 = gridQueue.front();
        if (node2->x == endX && node2->y == endY)
        {
            found = true;
            break;
        }

        cost++;

        std::queue<std::shared_ptr<Coord2D>> neighbourQueue;

        while (!gridQueue.empty())
        {
            neighbourQueue.push(gridQueue.front());
            gridQueue.pop();
        }

        while (!neighbourQueue.empty() && !found && count < MAX_LIMIT)
        {
            std::shared_ptr<Coord2D> node = neighbourQueue.front();

            if (node->x == endX && node->y == endY)
            {
                found = true;
                break;
            }

            neighbourQueue.pop();

            if (node->x > 0) //maybe this should be 1
            {
                int xx = (node->x)-1;
                int yy = (node->y);
                if (pathfindingGrid[xx][yy] == -1 && grid[xx][yy] == 0)
                {
                    pathfindingGrid[xx][yy] = cost;
                    neighbourQueue.push(std::make_shared<Coord2D>(xx, yy));
                }
            }

            if (node->x < GRID_MAP_WIDTH)
            {
                int xx = (node->x)+1;
                int yy = (node->y);
                if (pathfindingGrid[xx][yy] == -1 && grid[xx][yy] == 0)
                {
                    pathfindingGrid[xx][yy] = cost;
                    neighbourQueue.push(std::make_shared<Coord2D>(xx, yy));
                }
            }

            if (node->y > 1)
            {
                int xx = (node->x);
                int yy = (node->y)-1;
                if (pathfindingGrid[xx][yy] == -1 && grid[xx][yy] == 0)
                {
                    pathfindingGrid[xx][yy] = cost;
                    neighbourQueue.push(std::make_shared<Coord2D>(xx, yy));
                }
            }

            if (node->y < GRID_MAP_HEIGHT)
            {
                int xx = (node->x);
                int yy = (node->y)+1;
                if (pathfindingGrid[xx][yy] == -1 && grid[xx][yy] == 0)
                {
                    pathfindingGrid[xx][yy] = cost;
                    neighbourQueue.push(std::make_shared<Coord2D>(xx, yy));
                }
            }

            if (node->x == endX && node->y == endY)
            {
                found = true;
            }

            while (!neighbourQueue.empty())
            {
                gridQueue.push(neighbourQueue.front());
                neighbourQueue.pop();
            }
        }
        ++count;
    }

    // Debug code
    /*for (int i = 0; i < GRID_MAP_WIDTH; ++i)
    {
        for (int j = 0; j < GRID_MAP_HEIGHT; ++j)
        {
            std::cout << std::to_string(pathfindingGrid[i][j]);
            if (i == endX && j == endY)
            {
                std::cout << "x";
            }
            std::cout << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/

    if (!found)
    {
        return emptyPath;
    }

    pathfindingGrid[endX][endY] = cost++;
    path.push_back(std::make_shared<Coord2D>(endX,endY));

    int bestXGNode = endX;
    int bestYGNode = endY;

    count = 0;
    found = false;

    while (!found && count < MAX_LIMIT)
    {
        int tempX = bestXGNode;
        int tempY = bestYGNode;

        if (bestXGNode > 0)
        {
            int currentGridItem = pathfindingGrid[bestXGNode][bestYGNode];
            int compareToGridItem = pathfindingGrid[bestXGNode-1][bestYGNode];
            if (compareToGridItem < currentGridItem
                    && compareToGridItem != -1)
            {
                bestXGNode = bestXGNode-1;
                bestYGNode = bestYGNode;
            }
        }
        if (bestXGNode < GRID_MAP_WIDTH)
        {
            int currentGridItem = pathfindingGrid[bestXGNode][bestYGNode];
            int compareToGridItem = pathfindingGrid[bestXGNode+1][bestYGNode];
            if (compareToGridItem < currentGridItem
                    && compareToGridItem != -1)
            {
                bestXGNode = bestXGNode+1;
                bestYGNode = bestYGNode;
            }
        }

        if (bestYGNode > 0)
        {
            int currentGridItem = pathfindingGrid[bestXGNode][bestYGNode];
            int compareToGridItem = pathfindingGrid[bestXGNode][bestYGNode-1];
            if (compareToGridItem < currentGridItem
                    && compareToGridItem != -1)
            {
                bestXGNode = bestXGNode;
                bestYGNode = bestYGNode-1;
            }
        }
        if (bestYGNode < GRID_MAP_HEIGHT)
        {
            int currentGridItem = pathfindingGrid[bestXGNode][bestYGNode];
            int compareToGridItem = pathfindingGrid[bestXGNode][bestYGNode+1];
            if (compareToGridItem < currentGridItem
                    && compareToGridItem != -1)
            {
                bestXGNode = bestXGNode;
                bestYGNode = bestYGNode+1;
            }
        }

        if (bestXGNode == startX && bestYGNode == startY)
        {
            found = true;
            break;
        }

        // Bailout if haven't moved grid block
        if (tempX == bestXGNode && tempY == bestYGNode)
        {
            return emptyPath;
        }

        path.push_back(std::make_shared<Coord2D>(bestXGNode,bestYGNode));
        ++count;
    }
    std::reverse(std::begin(path), std::end(path));
    return path;
}

int Pathfinder::pathfindingGrid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT];
