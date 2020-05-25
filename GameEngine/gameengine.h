#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <memory>
#include <iostream>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <GL/glut.h>

#include "objects/object.h"
#include "npc.h"
#include "ai/gridnode.h"

#include "texture.h"

class GameEngine
{
public:
    static const int GRID_MAP_WIDTH = 30;
    static const int GRID_MAP_HEIGHT = 30;

    static SDL_GLContext mainContext;
    static SDL_Window *mainWindow;
    static std::string programName;
    static int width;
    static int height;
    static float fov;
    static int viewDistance;

    static std::vector<std::shared_ptr<Object>> objects;
    static std::vector<std::shared_ptr<NPC>> npcs;
    static std::vector<std::shared_ptr<Object>> gridCollisionFloor;
    static std::vector<std::shared_ptr<Object>> pathfinderPaths;

    static void checkSDLError(int line = -1);
    static void printSDLGLAttributes();
    static bool setOpenGLAttributes();

    static float angle;
    static float lx,lz;
    static float x, z;
    static float deltaAngle;
    static float deltaMove;
    static float forwardMovementSpeed;
    static float leftRightMovementSpeed;
    static int grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT];
    static int pathfindingGridCache[GRID_MAP_WIDTH][GRID_MAP_HEIGHT];
    static int pathfindingGrid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT];

    static SDL_GLContext ctx;
    static SDL_Window* window;

    static bool loop;

    // Map Data
    static float mostTop;
    static float mostBottom;
    static float mostLeft;
    static float mostRight;
    static float mapWidth;
    static float mapHeight;
    static float gridBlockWidth;
    static float gridBlockHeight;

    // Game engine methos
    static void init();
    static bool assets();
    static void draw();
    static void run(int argc, char **argv);
    static void runPhysics();
    static void cleanUp();

    static void test();



    static void setupMap();
    static void setupMapData();
    static void setupNpcs();

    // Pathfinding
    static void setupGrid();
    static std::vector<std::shared_ptr<GridNode>> generatePath(int startX, int startY, int endX, int endY);
    static void pathfinder();
    static int lastPlayerGridX, lastPlayerGridY;
    static const int MAX_LIMIT = 20000; // Max pathfinding iterations

    // User settings
    static int getWidth();
    static void setWidth(int w);
    static int getHeight();
    static void setHeight(int h);
    static float getFOV();
    static void setFOV(float f);
    static int getViewDistance();
    static void setViewDistance(int vd);
    static void computePos(float deltaMove);
    static void computeDir(float deltaAngle);
    static void movement();
    static void reshape(int w, int h);
    static void pressKey(int key, int xx, int yy);
    static void releaseKey(int key, int x, int y);
    static void processSpecialKeys(int key, int xx, int yy);

    // Helper methods
    static float toRadians(float degrees);
    static float aspectRatio(int width, int height);
    static float aspectRatio(float width, float height);
    static int x3DOpenGLGridTo2dGrid(float x);
    static float x2DGridTo3DOpenGLGrid(int x);
    static int y3DOpenGLGridTo2dGrid(float z);
    static float y2DGridTo3DOpenGLGrid(int y);

    // Assets
    static std::unordered_map<std::string, std::shared_ptr<Texture>>textures;

};

#endif // GAMEENGINE_H
