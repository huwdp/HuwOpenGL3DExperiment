#include "gameengine.h"

GameEngine::GameEngine()
{
    gameState = std::make_shared<GameState>();
}

bool GameEngine::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL\n";
        return false;
    }

    mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        getWidth(), getHeight(), SDL_WINDOW_OPENGL);

    if (!mainWindow)
    {
        std::cout << "Unable to create window\n";
        checkSDLError(__LINE__);
        return false;
    }

    mainContext = SDL_GL_CreateContext(mainWindow);

    setOpenGLAttributes();
    printSDLGLAttributes();

    SDL_GL_SetSwapInterval(1);



    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, width, height);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, getWidth(), getHeight(), 0, 1, -1);

    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);
    //glEnable(GL_CULL_FACE);

    gluPerspective(toRadians(getFOV()), aspectRatio(getWidth(), getHeight()), 0, getViewDistance());

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    gameState->addDrawable(std::move(std::make_shared<Tree>(0, 0, 1)));
    return true;
}

void GameEngine::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
        glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
        glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
        glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
    glEnd();

    std::vector<std::shared_ptr<Drawable>> drawables = gameState->getDrawables();
    for (std::vector<std::shared_ptr<Drawable>>::iterator it = drawables.begin(); it != drawables.end(); ++it)
    {
        (*it)->draw();
    }

    SDL_GL_SwapWindow(mainWindow);
}

void GameEngine::run()
{
    std::shared_ptr<Player> player = gameState->getPlayer();


    bool loop = true;

    while (loop)
    {
        glTranslatef(-player->getX(), -player->getY(), -player->getZ());

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                loop = false;
            }

            runPhysics();
            draw();

            std::shared_ptr<Player> player = gameState->getPlayer();

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    loop = false;
                    break;
                case SDLK_w:
                    player->setX(player->getX()+0.1f);
                    break;
                case SDLK_a:
                    player->setY(player->getX()-0.1f);
                    break;
                case SDLK_s:
                    player->setX(player->getX()-0.1f);
                    break;
                case SDLK_d:
                    player->setY(player->getX()+0.1f);
                    break;
                case SDLK_r:
                    // Cover with red and update
                    glClearColor(1.0, 0.0, 0.0, 1.0);
                    glClear(GL_COLOR_BUFFER_BIT);
                    break;
                case SDLK_KP_SPACE:
                    player->setZ(player->getZ() + 1.0f);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void GameEngine::cleanUp()
{
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

void GameEngine::runPhysics()
{
    std::shared_ptr<Player> player = gameState->getPlayer();
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

void GameEngine::setWidth(int width)
{
    this->width = width;
}
int GameEngine::getHeight()
{
    return height;
}
void GameEngine::setHeight(int height)
{
    this->height = height;
}

float GameEngine::getFOV()
{
    return fov;
}

void GameEngine::setFOV(float fov)
{
    this->fov = fov;
}

int GameEngine::getViewDistance()
{
    return viewDistance;
}

void GameEngine::setViewDistance(int viewDistance)
{
    this->viewDistance = viewDistance;
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
