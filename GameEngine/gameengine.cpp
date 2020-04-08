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
#include "player.h"


bool GameEngine::init()
{
    loop = true;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);            // Enable Z buffer test depth
    glEnable(GL_SMOOTH);                // Unknown
    //glEnable(GL_LIGHTING);            // Enable lighting - Will be useful in future!
    glEnable(GL_LINE_SMOOTH);           // Smooth lines
    glEnable(GL_POINT_SMOOTH);          // Smoooth points
    //glEnable(GL_CULL_FACE);           // Culling
    glHint(GL_LINE_SMOOTH, GL_NICEST);  // Smooth lines - Is this needed?
    glHint(GL_POINT_SMOOTH, GL_NICEST); // Smoooth points - Is this needed?

    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

    glEnable(GL_MULTISAMPLE);

    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
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
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;
    float ratio = 1.0* w / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(fov,ratio,1,1000);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);


    /*glLoadIdentity();
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(fov,(GLfloat)w/(GLfloat)h,1.0,200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
}

void GameEngine::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt(x, 1.0f, z, x+lx, 1.0f,  z+lz, 0.0f, 1.0f,  0.0f);

    // Draw ground
    glColor3f(0.0f, 0.3f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();


    // Draw solid dodecahedron
    glColor3f(0.0f, 0.0f, 0.7f);
    glTranslatef(-8.0f ,0.75f, 0.0f);
    glutSolidDodecahedron();


    // Draw solid wire torus
    glColor3f(0.0f, 0.0f, 0.7f);
    glTranslatef(2.0f ,0.0f, 0.0f);
    glutWireTorus(0.5, 0.5, 0.5, 0.5);

    // Draw solid cone
    glColor3f(0.0f, 0.0f, 0.7f);
    glTranslatef(2.0f ,0.0f, 0.0f);
    glutSolidCone(1, 1, 6, 6);


    glTranslatef(2.0f ,0.0f, 0.0f);
    glColor3f(2.0f, 0.0f, 0.0f);
    glutSolidSphere(0.5f,20,20);

    // Tree
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(2.0f ,0.75f, 0.0f);
    glutSolidCube(0.5);



    glColor3f(0.737255f, 0.560784f, 0.560784f);
    glTranslatef(2.0f ,0.0f, 0.0f);
    glutSolidTeapot(0.5);


    glColor3f(0.737255f, 0.560784f, 0.560784f);
    glTranslatef(2.0f ,0.0f, 0.0f);
    glutWireTeapot(0.5);

    glutSwapBuffers();
    glutPostRedisplay();
}

void GameEngine::run(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width,height);
    //glutInitWindowPosition(100,100);
    glutCreateWindow(programName.c_str());
    init();
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    //glutKeyboardFunc(keyboard);
    //glutSpecialFunc(pressKey);
    glutSpecialFunc(processSpecialKeys);
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
}

void GameEngine::runPhysics()
{
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

}

void GameEngine::processSpecialKeys(int key, int xx, int yy)
{
    std::cout << "Angle: " << angle << "Lx: " << lx << "Lz: " << lz << std::endl;

    float fraction = 0.1f;
    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

void GameEngine::releaseKey(int key, int x, int y)
{
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
SDL_GLContext GameEngine::ctx;
SDL_Window* GameEngine::window;

std::string GameEngine::programName = "Huw's OpenGL 3D experiment";
int GameEngine::width = 800;
int GameEngine::height = 800;
float GameEngine::fov = 90.0f;
int GameEngine::viewDistance = 0;

float GameEngine::angle = 0.0f;
float GameEngine::lx=0.0f;
float GameEngine::lz=-1.0f;
float GameEngine::x=0.0f;
float GameEngine::z=5.0f;
