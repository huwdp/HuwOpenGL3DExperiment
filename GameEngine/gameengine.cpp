#include <GL/glut.h> // Once you include glut.h (you don't need gl.h or glu.h)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <functional>

#include <random>
#include <iostream>
#include <memory>

#include "gameengine.h"


bool GameEngine::init()
{
    loop = true;



    /*
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    //Create window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow("SDL AR Example",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    if(window == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    //creating new context
    ctx = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);



    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    return true;
    */

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);


    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    // Setup the materials for LIGHT0

    // Enable the light
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);



    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
}

 void GameEngine::computePos(double deltaMove) {

    x += deltaMove * lx * 0.2f;
    z += deltaMove * lz * 0.2f;
}

void GameEngine::computeDir(double deltaAngle) {
    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

void GameEngine::reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,(GLfloat)w/(GLfloat)h,1.0,200.0);
    glMatrixMode(GL_MODELVIEW);
}

void GameEngine::draw()
{
    static float cube[8][3] = {
        {0.5, 0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5}
    };

    /* Do our drawing, too. */
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);


    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[2]);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[1]);

    glColor3f(0.0, 1.0, 1.0);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[6]);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);

    glColor3f(1.0, 0.0, 1.0);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[7]);


    glEnd();

    glMatrixMode(GL_MODELVIEW);
    //glRotatef(5.0, 1.0, 1.0, 1.0);
    glFlush();
    glutSwapBuffers();
    GLenum errCode;
    const GLubyte *errString;
    if((errCode = glGetError()) != GL_NO_ERROR)
    {
       errString = gluErrorString(errCode);
       fprintf (stderr,"OpenGL error : %s\n",errString);
    }

    glutPostRedisplay();
}

void GameEngine::run(int argc, char** argv)
{
    std::shared_ptr<Player> player = gameState.getPlayer();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(draw);
    //glutReshapeFunc(reshape, nullptr);

    //glutIdleFunc(spinTorus);

      //glutKeyboardFunc(keyboard);

    glutSpecialFunc(pressKey);


    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);

    glutMainLoop();
}

void GameEngine::cleanUp()
{
    if (ctx) {
        /* SDL_GL_MakeCurrent(0, NULL); *//* doesn't do anything */
        SDL_GL_DeleteContext(ctx);
    }
    SDL_DestroyWindow( window );
    SDL_Quit();
    //exit(rc);
}

void GameEngine::runPhysics()
{
    std::shared_ptr<Player> player = gameState.getPlayer();
    if (player->getZ() > 0)
    {
        player->setZ(player->getZ() - 0.1f);
    }
}

void GameEngine::checkSDLError(int line)
{
    std::string error = SDL_GetError();

    if (error != "")
    {
        std::cout << "SLD Error : " << error << std::endl;

        if (line != -1)
            std::cout << "\nLine : " << line << std::endl;

        SDL_ClearError();
    }
}

void GameEngine::pressKey(int key, int xx, int yy)
{
    switch (key) {
        case GLUT_KEY_LEFT:
            deltaAngle = -0.05f;
            std::cout << "LEFT" << deltaAngle;
        break;
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.05f;
            std::cout << "RIGHT";
        break;
        case GLUT_KEY_UP:
            deltaMove = 0.5f;
            std::cout << "UP";
        break;
        case GLUT_KEY_DOWN:
            deltaMove = -0.5f;
            std::cout << "DOWN";
        break;
    }
}

void GameEngine::releaseKey(int key, int x, int y)
{

    switch (key) {
        case GLUT_KEY_LEFT :
            std::cout << "LEFT" << deltaAngle;
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.0f;
        break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0;
        break;
    }
}

void GameEngine::printSDLGLAttributes()
{
    int value = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}

bool GameEngine::setOpenGLAttributes()
{
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    return true;
}

int GameEngine::getWidth()
{
    return width;
}

void GameEngine::setWidth(int w)
{
    width = w;
}

int GameEngine::getHeight()
{
    return height;
}

void GameEngine::setHeight(int h)
{
    height = h;
}

float GameEngine::getFOV()
{
    return fov;
}

void GameEngine::setFOV(float f)
{
    fov = f;
}

int GameEngine::getViewDistance()
{
    return viewDistance;
}

void GameEngine::setViewDistance(int vd)
{
    viewDistance = vd;
}

float GameEngine::toRadians(float degrees)
{
    return sin(degrees * M_PI / 180);
}

float GameEngine::aspectRatio(int width, int height)
{
    return width / height;
}

float GameEngine::aspectRatio(float width, float height)
{
    return width / height;
}

bool GameEngine::loop = true;
GameState GameEngine::gameState;
SDL_GLContext GameEngine::ctx;
SDL_Window* GameEngine::window;

int GameEngine::width = 0;
int GameEngine::height = 0;
float GameEngine::fov = 0;
int GameEngine::viewDistance = 0;

float GameEngine::angle = 0.0f;
float GameEngine::lx=0.0f;
float GameEngine::lz=-1.0f;
float GameEngine::x=0.0f;
float GameEngine::z=5.0f;
float GameEngine::deltaAngle = 0.0f;
float GameEngine::deltaMove = 0;
