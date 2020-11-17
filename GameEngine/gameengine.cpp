#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <functional>

#include <random>
#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>

#include "gameengine.h"
#include "player.h"
#include "objects/cube.h"
#include "objects/texturedcube.h"
#include "objects/floor.h"
#include "objects/skybox.h"

#include "ai/gridnode.h"

#include "ai/enemynpc.h"

#include "ai/pathfinder.h"

void GameEngine::init()
{
    loop = true;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);            // Enable Z buffer test depth
    glEnable(GL_SMOOTH);                // Unknown

    glEnable(GL_LINE_SMOOTH);           // Smooth lines
    glEnable(GL_POINT_SMOOTH);          // Smoooth points
    //glEnable(GL_CULL_FACE);           // Culling
    glHint(GL_LINE_SMOOTH, GL_NICEST);  // Smooth lines - Is this needed?
    glHint(GL_POINT_SMOOTH, GL_NICEST); // Smoooth points - Is this needed?

    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_3D);
    //glDepthFunc(GL_ALWAYS);
    //glDisable(GL_STENCIL_TEST);

    // Lighting
    glEnable(GL_LIGHTING);            // Enable lighting
    glEnable(GL_LIGHT0);
    //GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    //GLfloat mat_shininess[] = { 50.0 };
    //GLfloat light_position[] = { 1.0, 1.0, 2.0, 0.0 };

    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //GL_AMBIENT
    //GL_DIFFUSE
    //GL_SPECULAR




    ////// Lighting variables
    float ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f  };	// ambient light
    float diffuseLight[] = {1.0f, 1.0f, 1.0f, 1.0f };	// diffuse light
    float lightPosition[] = {10.0f, 10.0f, 10.0f, 0.0f };	// the light position

    ////// Material variables
    float matAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float matDiff[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    //float matAmbient1[] = { 0.8f, 0.3f, 0.8f, 1.0f };
    //float matDiff1[] = { 0.525f, 0.25f, 0.25f, 1.0f };

    float matAmbient2[] = { 1.f, 1.0f, 1.0f, 1.0f };
    float matDiff2[] = { 0.50f, 0.50f, 0.50f, 0.5f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff2);

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 3.0, 1.0, 0.0 };

    //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Setup the materials for LIGHT0
    //glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);

    // Now setup LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Enable the light
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
}

void GameEngine::reshape(int w, int h)
{
    if (h == 0)
    {
        h = 1;
    }

    float ratio = 1.0* w / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(fov,ratio,1,250);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void GameEngine::renderBitmapString(
    float x,
    float y,
    float z,
    void *font,
    char *string)
{
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void GameEngine::draw()
{
    runPhysics();
    movement();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // Run AI
    ai();

    // Reset transformations
    glLoadIdentity();


    if (mainMenuToggle)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        gluLookAt(0, 1.0f, 10, 0, 1.0f,  5, 0.0f, 1.5f,  0.0f);

        int xx = 0;
        int yy = 0;
        for (auto it = mainMenu.begin(); it != mainMenu.end(); ++it)
        {
            glColor3f(.0f, .0f, .0f);
            std::string menuText((*it).c_str());
            if (mainMenuSelectedItem == xx)
            {
                glColor3f(.0f, .0f, 1.0f);
                menuText.push_back('<');
            }
            char* chr = strdup(menuText.c_str());
            renderBitmapString(0, yy--, 0, GLUT_BITMAP_8_BY_13, chr);
            ++xx;
        }

        glutSwapBuffers();
        glutPostRedisplay();
        return;
    }
    glClearColor(0.f, 0.f, 0.f, 0.f);



    // Set the camera
    gluLookAt(x, y, z, x+lx, y,  z+lz, 0.0f, 1.5f,  0.0f);

    // Draw skybox
    auto skyBox = std::make_shared<SkyBox>(0.0f , 0.0f, 0.0f, 100.0f, 100.0f, 100.0f, 1.f, 1.f, 1.f, textures["sky"]);
    skyBox->draw();

    // Draw objects
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        glColor3f(1.0f, 1.0f, 1.0f); // Reset color
        (*it)->draw();
    }

    // Draw NPCs
    for (auto it = npcs.begin(); it != npcs.end(); ++it)
    {
        glColor3f(1.0f, 1.0f, 1.0f); // Reset color
        (*it)->draw();
    }

    // Draw grid floor collisions
    for (auto it = gridCollisionFloor.begin(); it != gridCollisionFloor.end(); ++it)
    {
        glColor3f(1.0f, 1.0f, 1.0f); // Reset color
        (*it)->draw();
    }

    // Draw shortest path
    for (auto it = pathfinderPaths.begin(); it != pathfinderPaths.end(); ++it)
    {
        glColor3f(1.0f, 1.0f, 1.0f); // Reset color
        (*it)->draw();
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

bool GameEngine::assets()
{
    textures["wood"] = std::make_shared<Texture>("textures/wood2.bmp");
    textures["wallpaper"] = std::make_shared<Texture>("textures/wall.bmp");
    textures["sky"] = std::make_shared<Texture>("textures/sky.bmp");
    textures["brick"] = std::make_shared<Texture>("textures/brick.bmp");

    /*for (std::unordered_map<std::string, std::make_shared<Texture>>::iterator it = textures.begin(); it != textures.end(); ++it)
    {
        std::shared_ptr<Texture> tex = (*it)->second;
        if (tex->load() != SUCCESS)
        {
            std::cout << "Error: Could not open \"" + tex->textureFileLocation + "\"" << std::endl;
            return false;
        }
    }*/
    return true;
}

void GameEngine::setupMap()
{
    // Floor
    objects.push_back(std::make_shared<Floor>(0.0f ,-1.0f, 0.0f, 30.0f, 0.1f, 30.0f, 0.f, 0.f, 0.f, textures["wood"]));



    // Walls
    objects.push_back(std::make_shared<TexturedCube>(0.0f ,1.0f, 30.0f, 30.0f, 1.0f, 3.0f, 1.f, 1.f, 1.f, textures["brick"]));
    objects.push_back(std::make_shared<TexturedCube>(0.0f ,1.0f, -30.0f, 30.0f, 0.3f, 3.0f, 1.f, 1.f, 1.f, textures["brick"]));
    objects.push_back(std::make_shared<TexturedCube>(30.0f ,1.0f, 0.0f, 0.3f, 30.0f, 3.0f, 1.f, 1.f, 1.f, textures["brick"]));
    objects.push_back(std::make_shared<TexturedCube>(-30.0f ,1.0f, 0.0f, 0.3f, 30.0f, 3.0f, 1.f, 1.f, 1.f, textures["brick"]));

    // Middle wall
    objects.push_back(std::make_shared<TexturedCube>(-20.0f ,1.0f, 0.0f, 0.3f, 10.0f, 3.0f, 1.f, 1.f, 1.f, textures["wallpaper"]));

    // Objects
    objects.push_back(std::make_shared<TexturedCube>(0.0f ,2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.f, 1.f, 1.f, textures["wood"]));
    objects.push_back(std::make_shared<Cube>(10.0f ,0.2f, 2.0f, 1.0f, 1.f, 0.f, 0.f));
    objects.push_back(std::make_shared<Cube>(10.0f ,0.4f, 6.0f, 1.0f, 0.f, 1.f, 0.f));
    objects.push_back(std::make_shared<Cube>(10.0f ,0.4f, 16.0f, 2.0f, 0.f, 0.f, 1.f));
    objects.push_back(std::make_shared<Cube>(-10.0f ,1.0f, -10.0f, 2.0f, 0.f, 0.f, 1.f));
    objects.push_back(std::make_shared<TexturedCube>(-10.0f ,1.0f, -10.0f, 1.0f, 1.0f, 1.0f, 1.f, 1.f, 1.f, textures["wallpaper"]));
    objects.push_back(std::make_shared<Cube>(10.0f ,1.0f, -10.0f, 2.0f, 0.f, 0.f, 1.f));
    objects.push_back(std::make_shared<Cube>(-10.0f ,1.0f, 10.0f, 2.0f, 0.f, 0.f, 1.f));
    objects.push_back(std::make_shared<Cube>(10.0f ,1.0f, 10.0f, 2.0f, 0.f, 0.f, 1.f));
    objects.push_back(std::make_shared<Cube>(0.0f ,0.0f, 0.0f, 2.0f, 0.f, 0.f, 1.f));

    // NPCs
    npcs.push_back(std::make_shared<EnemyNPC>("Troll", 10.0f ,0.5f, 10.0f));
    npcs.push_back(std::make_shared<EnemyNPC>("Troll", 20.0f ,0.5f, -10.0f));
}

void GameEngine::setupPlayer()
{
    // Set player camera height
    y = 1.5f;
}

void GameEngine::setupNpcs()
{
    //objects.push_back(std::make_shared<NPC>(20.0f ,0.0f, 20.0f, 0.5f, 0.5f, 2.0f, 1.0f, 1.f, 1.f, textures["wallpaper"]));
}

void GameEngine::setupMapData()
{
    mostTop = 0.0f;
    mostBottom = 0.0f;
    mostLeft = 0.0f;
    mostRight = 0.0f;

    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        auto obj = (*it);
        if (obj->x-obj->width/2 < mostLeft)
        {
            mostLeft = obj->x-obj->width/2;
        }
        if (obj->x+obj->width/2 > mostRight)
        {
            mostRight = obj->x+obj->width/2;
        }
        if (obj->z-obj->length/2 < mostTop)
        {
            mostTop = obj->z-obj->length/2;
        }
        if (obj->z+obj->length/2 > mostBottom)
        {
            mostBottom = obj->z+obj->length/2;
        }
    }

    mapWidth = mostRight-mostLeft;
    mapHeight = mostBottom-mostTop;
    gridBlockWidth = mapWidth/GRID_MAP_WIDTH;
    gridBlockHeight = mapHeight/GRID_MAP_HEIGHT;
}

void GameEngine::setupGrid()
{
    for (int i = 0; i < GRID_MAP_WIDTH; ++i)
    {
        for (int j = 0; j < GRID_MAP_WIDTH; ++j)
        {
            grid[i][j] = 0;
        }
    }

    // Optimise this in the future
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        auto obj = (*it);
        if (obj->collidable)
        {
            int leftSideOfObject = obj->x-obj->width/2;
            int rightSideOfObject = obj->x+obj->width/2;

            int topSideOfObject = obj->z-obj->length/2;
            int bottomSideOfObject = obj->z+obj->length/2;

            // Center
            //grid[x3DOpenGLGridTo2dGrid(obj->x)][y3DOpenGLGridTo2dGrid(obj->z)] = 1;

            int mostLeftOfObj = x3DOpenGLGridTo2dGrid(obj->x-obj->width/2);
            int mostRightOfObj = x3DOpenGLGridTo2dGrid(obj->x+obj->width/2);

            int mostTopOfObj = x3DOpenGLGridTo2dGrid(obj->z-obj->length/2);
            int mostBottomOfObj = x3DOpenGLGridTo2dGrid(obj->z+obj->length/2);

            for (int i = mostLeftOfObj; i <= mostRightOfObj; ++i)
            {
                for (int j = mostTopOfObj; j <= mostBottomOfObj; ++j)
                {
                    grid[i][j] = 1;
                }
            }

            // Slow collision decection method (needs to be removed)
            for (int i = 0; i < GRID_MAP_WIDTH; ++i)
            {
                for (int j = 0; j < GRID_MAP_WIDTH; ++j)
                {
                    bool xInside = false;
                    bool zInside = false;

                    if (leftSideOfObject < mostLeft+i*gridBlockWidth && rightSideOfObject > mostLeft+(i*gridBlockWidth)+gridBlockWidth)//&& rightSideOfObject >= i+gridBlockWidth)
                    {
                        xInside = true;
                    }

                    if (topSideOfObject < mostTop+j*gridBlockHeight && bottomSideOfObject > mostTop+(j*gridBlockHeight)+gridBlockHeight)//&& rightSideOfObject >= i+gridBlockWidth)
                    {
                        zInside = true;
                    }

                    if (xInside && zInside)
                    {
                        grid[i][j] = 1;
                    }

                }
            }
        }
    }

    // Optional
    // Draw grid map (Optional)
    for (int i = 0; i < GRID_MAP_WIDTH; ++i)
    {
        for (int j = 0; j < GRID_MAP_HEIGHT; ++j)
        {
            if (grid[i][j] == 1)
            {
                //gridCollisionFloor.push_back(std::make_shared<Floor>(mostLeft+i*gridBlockWidth ,-0.9f, mostTop+j*gridBlockHeight, gridBlockWidth/2, gridBlockHeight/2, 0.1f, 0.f, 1.f, 0.f, textures["wallpaper"]));
                gridCollisionFloor.push_back(std::make_shared<Floor>(x2DGridTo3DOpenGLGrid(i),
                                                                     -0.9f,
                                                                     y2DGridTo3DOpenGLGrid(j),
                                                                     gridBlockWidth/2,
                                                                     0.1f,
                                                                     gridBlockHeight/2,
                                                                     0.f,
                                                                     1.f,
                                                                     0.f,
                                                                     textures["wallpaper"]));
            }
        }
    }
}

void GameEngine::ai()
{
    // Recalculate gridWidth and gridHeight
    pathfinderPaths.clear();
    for (auto it = npcs.begin(); it != npcs.end(); ++it)
    {
        auto npc = (*it);
        if (x > npc->x - 5 && x < npc->x+5
                && npc->z > npc->z - 5 && npc->z < npc->z+5)
        {
            npc->onAlert = true;
            int xx = x3DOpenGLGridTo2dGrid(x);
            int yy = y3DOpenGLGridTo2dGrid(z);

            int npcX = x3DOpenGLGridTo2dGrid(npc->x);
            int npcZ = y3DOpenGLGridTo2dGrid(npc->z);

            std::vector<std::shared_ptr<GridNode>> path = Pathfinder::generatePath(grid, npcX, npcZ, xx, yy);

            for (auto it = path.begin(); it != path.end(); ++it)
            {
                std::shared_ptr<GridNode> gNode = (*it);
                int bob = x2DGridTo3DOpenGLGrid(gNode->x);
                pathfinderPaths.push_back(std::make_shared<Floor>(bob,
                                                                  -0.9f,
                                                                  y2DGridTo3DOpenGLGrid(gNode->y),
                                                                  gridBlockWidth/2,
                                                                  0.1f,
                                                                  gridBlockHeight/2,
                                                                  0.f,
                                                                  1.f,
                                                                  0.f,
                                                                  textures["wallpaper"]));
            }
        }
        else
        {
            npc->onAlert = false;
        }
    }
}

void GameEngine::setupMainMenu()
{
    mainMenuToggle = true;
    mainMenuSelectedItem = 0;
    mainMenu.push_back("Play game");
    mainMenu.push_back("Settings");
    mainMenu.push_back("Exit");
}

void GameEngine::run(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutCreateWindow(programName.c_str());
    init();
    if (!assets())
    {
        return;
    }
    setupPlayer();
    setupMainMenu();
    setupMap();
    setupMapData();
    setupNpcs();
    setupGrid();
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutIgnoreKeyRepeat(1);
    //glutSpecialFunc(pressKey);dddd
    //glutSpecialUpFunc(releaseKey);
    glutKeyboardUpFunc(keyUp);
    //glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);
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
    // 1.5 is player height
    if (jump)
    {
        if (y >= 3.0f) // Player max jump
        {
            jump = false;
        }
        y = y + 0.08f;
    }
    else
    {
        if (y > 1.5f)
        {
            y = y - 0.1f;
            if (y < 1.5f)
            {
                y = 1.5f;
            }
        }
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

void GameEngine::processSpecialKeys(int key, int xx, int yy)
{
    if (mainMenuToggle)
    {
        switch (key) {
            case GLUT_KEY_DOWN:
                if (mainMenuSelectedItem < mainMenu.size()-1)
                {
                    mainMenuSelectedItem++;
                }
                break;
            case GLUT_KEY_UP:
                if (mainMenuSelectedItem > 0)
                {
                    mainMenuSelectedItem--;
                }
                break;
        }
    }
}

void GameEngine::processNormalKeys(unsigned char key, int xx, int yy)
{
    if (mainMenuToggle)
    {
        switch (key)
        {
            case 13:    // Enter
                if (mainMenuSelectedItem == 0) // Play game menu item
                    mainMenuToggle = false;
                if (mainMenuSelectedItem == 2) // Exit game
                    exit(0);
                break;
            case 119:
                if (mainMenuSelectedItem > 0)
                {
                    mainMenuSelectedItem--;
                }
            break;
        case 115:
            if (mainMenuSelectedItem < mainMenu.size()-1)
            {
                mainMenuSelectedItem++;
            }
            break;
        }
        return;
    }
    switch (key) {
        case 27:    // Esc
            mainMenuToggle = true;
            break;
    }
    switch (key) {
        case 'w' : deltaMove = forwardMovementSpeed; break;
        case 'a' : deltaAngle = -leftRightMovementSpeed; break;
        case 's' : deltaMove = -forwardMovementSpeed; break;
        case 'd' : deltaAngle = leftRightMovementSpeed; break;
        case ' ' :
            if (y == 1.5) // player height
            {
                jump = true;
            }
        break;
    }
}

void GameEngine::pressKey(int key, int xx, int yy)
{
    if (mainMenuToggle)
    {
        return;
    }
    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -leftRightMovementSpeed; break;
        case GLUT_KEY_RIGHT : deltaAngle = leftRightMovementSpeed; break;
        case GLUT_KEY_UP : deltaMove = forwardMovementSpeed; break;
        case GLUT_KEY_DOWN : deltaMove = -forwardMovementSpeed; break;
    }
}

void GameEngine::releaseKey(int key, int x, int y)
{
    if (mainMenuToggle)
    {
        return;
    }
    /*switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f; break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0; break;
    }*/
}

void GameEngine::keyUp(unsigned char key, int x, int y)
{
    if (mainMenuToggle)
    {
        return;
    }
    switch (key) {
        case 'a' :
        case 'd' : deltaAngle = 0.0f; break;
        case 'w' :
        case 's' : deltaMove = 0; break;
    }
}

void GameEngine::keyDown(unsigned char key, int x, int y)
{

}

void GameEngine::computePos(float deltaMove)
{
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void GameEngine::computeDir(float deltaAngle)
{

    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

void GameEngine::movement()
{
    float oldX = x;
    float oldZ = z;

    if (deltaMove)
            computePos(deltaMove);
    if (deltaAngle)
        computeDir(deltaAngle);

    // Collision detection
    float offset = 0.0f;
    bool collision = false;
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        auto box = (*it);
        if (box->collidable)
        {
            box->collision = false;

            float left = (box->x - box->width-offset);
            float right = (box->x + box->width+offset);
            float top = (box->z - box->length-offset);
            float bottom = (box->z + box->length+offset);

            if (x > left &&
                x < right &&
                z > top &&
                z < bottom
                    )
            {
                collision = true;
                box->collision = true;
                break;
            }
        }
    }

    if (oldX != x || oldZ != z)
    {
        //pathfinder();
    }

    if (collision)
    {
        x = oldX;
        z = oldZ;
        return;
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

int GameEngine::x3DOpenGLGridTo2dGrid(float x)
{
    return (x-mostLeft)/2;
}

float GameEngine::x2DGridTo3DOpenGLGrid(int x)
{
    return mostLeft+x*gridBlockWidth;
}

int GameEngine::y3DOpenGLGridTo2dGrid(float z)
{
    return (z-mostTop)/2;
}

float GameEngine::y2DGridTo3DOpenGLGrid(int y)
{
    return mostTop+y*gridBlockHeight;
}

bool GameEngine::loop = true;
SDL_GLContext GameEngine::ctx;
SDL_Window* GameEngine::window;

std::vector<std::shared_ptr<Object>> GameEngine::objects;
std::vector<std::shared_ptr<AINPC>> GameEngine::npcs;
std::vector<std::shared_ptr<Object>> GameEngine::gridCollisionFloor;
std::vector<std::shared_ptr<Object>> GameEngine::pathfinderPaths;

std::string GameEngine::programName = "Huw's OpenGL 3D experiment";
int GameEngine::width = 800;
int GameEngine::height = 800;
float GameEngine::fov = 90.0f;
int GameEngine::viewDistance = 0;

float GameEngine::angle = 0.0f;
float GameEngine::lx=0.0f;
float GameEngine::lz=-1.0f;
float GameEngine::x=0.0f;
float GameEngine::y=1.0f;
float GameEngine::z=5.0f;
float GameEngine::deltaAngle = 0.0f;
float GameEngine::deltaMove = 0;
float GameEngine::forwardMovementSpeed = 0.8f;
float GameEngine::leftRightMovementSpeed = 0.1f;
bool GameEngine::jump = false;

std::unordered_map<std::string, std::shared_ptr<Texture>> GameEngine::textures;

std::vector<std::string> GameEngine::mainMenu;
bool GameEngine::mainMenuToggle;
int GameEngine::mainMenuSelectedItem;

int GameEngine::grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT];

int GameEngine::lastPlayerGridX = 0;
int GameEngine::lastPlayerGridY = 0;
float GameEngine::mostTop;
float GameEngine::mostBottom;
float GameEngine::mostLeft;
float GameEngine::mostRight;
float GameEngine::mapWidth;
float GameEngine::mapHeight;
float GameEngine::gridBlockWidth = 1;
float GameEngine::gridBlockHeight = 1;
