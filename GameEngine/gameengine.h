#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <memory>
#include <iostream>

#include "gamestate.h"
#include "Assets/tree.h"
#include <GL/glew.h>

// SDL2 Headers
#include <SDL2/SDL.h>
#include <math.h>

class GameEngine
{
private:
    std::shared_ptr<GameState> gameState;
    SDL_GLContext mainContext;
    SDL_Window *mainWindow;
    std::string programName = "Game Engine";
    int width = 600;
    int height = 600;
    float fov = 90;
    int viewDistance = 100;

    void checkSDLError(int line = -1);
    void printSDLGLAttributes();
    bool setOpenGLAttributes();
public:
    GameEngine();
    bool init();
    void draw();
    void run();
    void runPhysics();
    void cleanUp();

    void test();

    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
    float getFOV();
    void setFOV(float fov);
    int getViewDistance();
    void setViewDistance(int viewDistance);

    // Helper methods
    float toRadians(float degrees);
    float aspectRatio(int width, int height);
    float aspectRatio(float width, float height);

};

#endif // GAMEENGINE_H
