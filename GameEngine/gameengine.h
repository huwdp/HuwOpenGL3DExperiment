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

#include "texture.h"

class GameEngine
{
public:
    static const int GRID_MAP_WIDTH = 200;
    static const int GRID_MAP_HEIGHT = 200;
    static float gridBlockWidth;
    static float gridBlockHeight;

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

    static SDL_GLContext ctx;
    static SDL_Window* window;

    static bool loop;

    static void init();
    static bool assets();
    static void draw();
    static void run(int argc, char **argv);
    static void runPhysics();
    static void cleanUp();

    static void test();

    static void computePos(float deltaMove);
    static void computeDir(float deltaAngle);
    static void movement();

    static void reshape(int w, int h);

    static void pressKey(int key, int xx, int yy);
    static void releaseKey(int key, int x, int y);
    static void processSpecialKeys(int key, int xx, int yy);

    static void setupMap();
    static void setupNpcs();

    // Pathfinding
    static void setupGrid();

    static int getWidth();
    static void setWidth(int w);
    static int getHeight();
    static void setHeight(int h);
    static float getFOV();
    static void setFOV(float f);
    static int getViewDistance();
    static void setViewDistance(int vd);

    // Helper methods
    static float toRadians(float degrees);
    static float aspectRatio(int width, int height);
    static float aspectRatio(float width, float height);

    // Assets
    static std::unordered_map<std::string, std::shared_ptr<Texture>>textures;

};

#endif // GAMEENGINE_H
