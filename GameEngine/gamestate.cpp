#include "gamestate.h"

GameState::GameState()
{
    drawables = std::vector<std::shared_ptr<Drawable>>();
    players = std::vector<std::shared_ptr<Player>>();
    player = std::make_shared<Player>();
}

std::vector<std::shared_ptr<Drawable>> GameState::getDrawables()
{
    return drawables;
}

void GameState::setDrawables(std::vector<std::shared_ptr<Drawable>> drawables)
{
    this->drawables = drawables;
}

void GameState::addDrawable(std::shared_ptr<Drawable> drawable)
{
    this->drawables.push_back(std::move(drawable));
}

std::vector<std::shared_ptr<Player>> GameState::getPlayers()
{
    return players;
}

void GameState::setPlayers(std::vector<std::shared_ptr<Player>> players)
{
    this->players = players;
}

std::shared_ptr<Player> GameState::getPlayer()
{
    return player;
}

void GameState::setPlayer(std::shared_ptr<Player> player)
{
    this->player = player;
}
