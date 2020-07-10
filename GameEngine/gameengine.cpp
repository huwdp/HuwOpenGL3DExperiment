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

#include "ai/gridnode.h"

void GameEngine::init()
{
    loop = true;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);            // Enable Z buffer test depth
    glEnable(GL_SMOOTH);                // Unknown

    glEnable(GL_LINE_SMOOTH);           // Smooth lines
    glEnable(GL_POINT_SMOOTH);          // Smoooth points
    glEnable(GL_CULL_FACE);           // Culling
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

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Setup the materials for LIGHT0
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);

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
    gluPerspective(fov,ratio,1,100);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void GameEngine::pathfinder()
{
    //std::vector<std::shared_ptr<GridNode>> path = generatePath(30, 26, 0, 0);

    //int xx = ((x-mostLeft)/2);
    //int yy = ((z-mostTop)/2);

    int xx = x3DOpenGLGridTo2dGrid(x);
    int yy = y3DOpenGLGridTo2dGrid(z);

    //std::cout << x << ":" << z << std::endl;
    //std::cout << mostLeft << ":" << mostTop << std::endl;
    //std::cout << xx << ":" << yy << std::endl;

    std::vector<std::shared_ptr<GridNode>> path = generatePath(15, 15, xx, yy);
    //std::vector<std::shared_ptr<GridNode>> path = generatePath(0, 0, 50, 0);
    pathfinderPaths.clear();
    for (auto it = path.begin(); it != path.end(); ++it)
    {
        std::shared_ptr<GridNode> gNode = (*it);
        //float xFloor = (gNode->x*gridBlockWidth)-(mapWidth/2);
        //float zFloor = (gNode->y*gridBlockHeight)-(mapHeight/2);
        pathfinderPaths.push_back(std::make_shared<Floor>(x2DGridTo3DOpenGLGrid(gNode->x),
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

std::vector<std::shared_ptr<GridNode>> GameEngine::generatePath(int startX, int startY, int endX, int endY)
{
    std::vector<std::shared_ptr<GridNode>> path;
    std::vector<std::shared_ptr<GridNode>> emptyPath;

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
    std::queue<std::shared_ptr<GridNode>> gridQueue;  // Convert to priority queue for better performance
    gridQueue.push(std::make_shared<GridNode>(startX, startY));
    pathfindingGrid[startX][startY] = cost;

    while (!gridQueue.empty() && !found && count < MAX_LIMIT)
    {
        std::shared_ptr<GridNode> node2 = gridQueue.front();
        if (node2->x == endX && node2->y == endY)
        {
            found = true;
            break;
        }

        cost++;

        std::queue<std::shared_ptr<GridNode>> neighbourQueue;

        while (!gridQueue.empty())
        {
            neighbourQueue.push(gridQueue.front());
            gridQueue.pop();
        }

        while (!neighbourQueue.empty() && !found && count < MAX_LIMIT)
        {
            std::shared_ptr<GridNode> node = neighbourQueue.front();

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
                    neighbourQueue.push(std::make_shared<GridNode>(xx, yy));
                }
            }

            if (node->x < GRID_MAP_WIDTH)
            {
                int xx = (node->x)+1;
                int yy = (node->y);
                if (pathfindingGrid[xx][yy] == -1 && grid[xx][yy] == 0)
                {
                    pathfindingGrid[xx][yy] = cost;
                    neighbourQueue.push(std::make_shared<GridNode>(xx, yy));
                }
            }

            if (node->y > 1)
            {
                int xx = (node->x);
                int yy = (node->y)-1;
                if (pathfindingGrid[xx][yy] == -1 && grid[xx][yy] == 0)
                {
                    pathfindingGrid[xx][yy] = cost;
                    neighbourQueue.push(std::make_shared<GridNode>(xx, yy));
                }
            }

            if (node->y < GRID_MAP_HEIGHT)
            {
                int xx = (node->x);
                int yy = (node->y)+1;
                if (pathfindingGrid[xx][yy] == -1 && grid[xx][yy] == 0)
                {
                    pathfindingGrid[xx][yy] = cost;
                    neighbourQueue.push(std::make_shared<GridNode>(xx, yy));
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
    path.push_back(std::make_shared<GridNode>(endX,endY));

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

        path.push_back(std::make_shared<GridNode>(bestXGNode,bestYGNode));
        ++count;
    }
    std::reverse(std::begin(path), std::end(path));
    return path;
}

void GameEngine::draw()
{
    movement();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt(x, 1.0f, z, x+lx, 1.0f,  z+lz, 0.0f, 1.5f,  0.0f);

    // Draw objects
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        //glColor3f(1.0f, 1.0f, 1.0f); // Reset color
        (*it)->draw();
    }

    // Draw grid floor collisions
    for (auto it = gridCollisionFloor.begin(); it != gridCollisionFloor.end(); ++it)
    {
        //glColor3f(1.0f, 1.0f, 1.0f); // Reset color
        (*it)->draw();
    }

    // Draw shortest path
    for (auto it = pathfinderPaths.begin(); it != pathfinderPaths.end(); ++it)
    {
        //glColor3f(1.0f, 1.0f, 1.0f); // Reset color
        (*it)->draw();
    }

    /*
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



    // Draw solid cone
    glColor3f(0.0f, 0.0f, 0.7f);
    glTranslatef(2.0f ,0.0f, 0.0f);
    glutSolidCone(1, 1, 6, 6);
    */

    glutSwapBuffers();
    glutPostRedisplay();
}

bool GameEngine::assets()
{
    textures["wood"] = std::make_shared<Texture>("textures/wood.bmp");
    textures["wallpaper"] = std::make_shared<Texture>("textures/wall.bmp");

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
    objects.push_back(std::make_shared<Floor>(0.0f ,-1.0f, 0.0f, 30.0f, 0.1f, 30.0f, 0.f, 1.f, 0.f, textures["wood"]));

    //objects.push_back(std::make_shared<Cube>(-10.0f ,1.0f, -10.0f, 2.0f, 0.f, 0.f, 1.f));

    objects.push_back(std::make_shared<TexturedCube>(-10.0f ,1.0f, -10.0f, 1.0f, 1.0f, 1.0f, 1.f, 1.f, 1.f, textures["wallpaper"]));

    objects.push_back(std::make_shared<Cube>(10.0f ,1.0f, -10.0f, 2.0f, 0.f, 0.f, 1.f));
    objects.push_back(std::make_shared<Cube>(-10.0f ,1.0f, 10.0f, 2.0f, 0.f, 0.f, 1.f));
    objects.push_back(std::make_shared<Cube>(10.0f ,1.0f, 10.0f, 2.0f, 0.f, 0.f, 1.f));

    objects.push_back(std::make_shared<Cube>(0.0f ,0.0f, 0.0f, 2.0f, 0.f, 0.f, 1.f));

    // Walls
    objects.push_back(std::make_shared<TexturedCube>(0.0f ,1.0f, 30.0f, 30.0f, 1.0f, 2.0f, 1.f, 1.f, 1.f, textures["wallpaper"]));
    objects.push_back(std::make_shared<TexturedCube>(0.0f ,1.0f, -30.0f, 30.0f, 0.3f, 2.0f, 1.f, 1.f, 1.f, textures["wallpaper"]));
    objects.push_back(std::make_shared<TexturedCube>(30.0f ,1.0f, 0.0f, 0.3f, 30.0f, 2.0f, 1.f, 1.f, 1.f, textures["wallpaper"]));
    objects.push_back(std::make_shared<TexturedCube>(-30.0f ,1.0f, 0.0f, 0.3f, 30.0f, 2.0f, 1.f, 1.f, 1.f, textures["wallpaper"]));

    // Middle wall
    objects.push_back(std::make_shared<TexturedCube>(-20.0f ,1.0f, 0.0f, 0.3f, 10.0f, 2.0f, 1.f, 1.f, 1.f, textures["wallpaper"]));

    // Objects
    objects.push_back(std::make_shared<TexturedCube>(0.0f ,2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.f, 1.f, 1.f, textures["wood"]));
    objects.push_back(std::make_shared<Cube>(10.0f ,0.2f, 2.0f, 1.0f, 1.f, 0.f, 0.f));
    objects.push_back(std::make_shared<Cube>(10.0f ,0.4f, 6.0f, 1.0f, 0.f, 1.f, 0.f));
    objects.push_back(std::make_shared<Cube>(10.0f ,0.4f, 16.0f, 2.0f, 0.f, 0.f, 1.f));
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
    setupMap();
    setupMapData();
    setupNpcs();
    setupGrid();
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    //glutKeyboardFunc(keyboard);
    //glutSpecialFunc(pressKey);
    glutSpecialFunc(processSpecialKeys);
    glutIgnoreKeyRepeat(1);
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

void GameEngine::processSpecialKeys(int key, int xx, int yy)
{
    /*std::cout << "Angle: " << angle << "Lx: " << lx << "Lz: " << lz << std::endl;

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
    }*/
}

void GameEngine::pressKey(int key, int xx, int yy)
{

    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -leftRightMovementSpeed; break;
        case GLUT_KEY_RIGHT : deltaAngle = leftRightMovementSpeed; break;
        case GLUT_KEY_UP : deltaMove = forwardMovementSpeed; break;
        case GLUT_KEY_DOWN : deltaMove = -forwardMovementSpeed; break;
    }
}

void GameEngine::releaseKey(int key, int x, int y)
{

    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f; break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0; break;
    }
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
        pathfinder();
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
std::vector<std::shared_ptr<NPC>> GameEngine::npcs;
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
float GameEngine::z=5.0f;
float GameEngine::deltaAngle = 0.0f;
float GameEngine::deltaMove = 0;
float GameEngine::forwardMovementSpeed = 0.8f;
float GameEngine::leftRightMovementSpeed = 0.1f;

std::unordered_map<std::string, std::shared_ptr<Texture>> GameEngine::textures;

int GameEngine::grid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT];

int GameEngine::pathfindingGrid[GRID_MAP_WIDTH][GRID_MAP_HEIGHT];
int GameEngine::lastPlayerGridX = 0;
int GameEngine::lastPlayerGridY = 0;
float GameEngine::mostTop;
float GameEngine::mostBottom;
float GameEngine::mostLeft;
float GameEngine::mostRight;
float GameEngine::mapWidth;
float GameEngine::mapHeight;
float GameEngine::gridBlockWidth;
float GameEngine::gridBlockHeight;
