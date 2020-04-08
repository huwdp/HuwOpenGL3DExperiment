#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <memory>
#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <GL/glut.h>

class GameEngine
{
public:

    static SDL_GLContext mainContext;
    static SDL_Window *mainWindow;
    static std::string programName;
    static int width;
    static int height;
    static float fov;
    static int viewDistance;

    static void checkSDLError(int line = -1);
    static void printSDLGLAttributes();
    static bool setOpenGLAttributes();

    static float angle;
    static float lx,lz;
    static float x, z;
    static float deltaAngle;
    static float deltaMove;

    static SDL_GLContext ctx;
    static SDL_Window* window;

    static bool loop;

    static bool init();
    static void draw();
    static void run(int argc, char **argv);
    static void runPhysics();
    static void cleanUp();

    static void test();

    static void computePos(double deltaMove);
    static void computeDir(double deltaAngle);
    static void reshape(int w, int h);

    static void pressKey(int key, int xx, int yy);
    static void releaseKey(int key, int x, int y);
    static void processSpecialKeys(int key, int xx, int yy);



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

};

#endif // GAMEENGINE_H
