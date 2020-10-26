#ifndef AINPC_H
#define AINPC_H

#include <string>


class AINPC
{
public:
    std::string name;
    int health = 100;
    float x;
    float y;
    float z;
    bool onAlert = false;
    AINPC(std::string name, float x, float y, float z)
    {
        this->name = name;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    //void moveTo(int x, int y) = 0;
    //void follow(std::shared<NPC> npc) = 0;
    virtual void draw() = 0;
};

#endif // AINPC_H
