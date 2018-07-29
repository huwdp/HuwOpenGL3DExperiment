#include "player.h"

Player::Player() : Coord(0.0, 0.0, 0.0)
{

}

Player::Player(float x, float y, float z) : Coord(x, y, z)
{

}

Player::Player(std::string name) : Coord()
{
    this->name = name;
}

float Player::getLx()
{
    return lx;
}

void Player::setLx(float lx)
{
    this->lx = lx;
}

float Player::getLz()
{
    return lz;
}

void Player::setLz(float lz)
{
    this->lz = lz;
}
