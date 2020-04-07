#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <memory>

#include "player.h"
#include "Assets/drawable.h"

class GameState
{
private:
    int mapWidth = 1000;
    int mapHeight = 100;
    int mapLength = 1000;

    int maxObjectWidth = 10;
    int maxObjectHeight = 10;
    int maxObjectLength = 10;

    std::vector<std::shared_ptr<Drawable>> drawables;
    std::vector<std::shared_ptr<Player>> players;

    std::shared_ptr<Player> player;


    double angle = 0.0;
    double lx=0.0,lz=-1.0;
    double x=0.0, z=10.0;
    double deltaAngle = 0.0;
    double deltaMove = 0;

public:
    GameState();
    std::vector<std::shared_ptr<Drawable>> getDrawables();
    void setDrawables(std::vector<std::shared_ptr<Drawable>> drawables);
    void addDrawable(std::shared_ptr<Drawable> drawable);

    std::vector<std::shared_ptr<Player>> getPlayers();
    void setPlayers(std::vector<std::shared_ptr<Player>> players);

    void pressKey(int key, int xx, int yy);
    void releaseKey(int key, int x, int y);

    void reshape(int w, int h);

    std::shared_ptr<Player> getPlayer();
    void setPlayer(std::shared_ptr<Player> player);
};

#endif // GAMESTATE_H
