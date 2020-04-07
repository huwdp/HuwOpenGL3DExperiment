#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "coord.h"

class Player : public Coord
{
private:
    std::string name;
    float lx = 0.0;
    float lz = -1.0f;
    float height = 0.0f;
public:
    Player();
    Player(float x, float y, float z);
    Player(std::string name);
    float getLx();
    void setLx(float lx);
    float getLz();
    void setLz(float lz);
    float getHeight();
    void setHeight(float height);
};

#endif // PLAYER_H
