#ifndef AINPC_H
#define AINPC_H

#include <string>
#include <stack>
#include <memory>
#include <ctime>
#include "aistateobj.h"

class AINPC
{
public:
    std::string name;
    int health = 100;
    float x;
    float y;
    float z;
    bool onAlert = false;
    std::stack<std::shared_ptr<AIStateObj>> stateStack;
    std::time_t lastTimeHealed;
    AINPC(std::string name, float x, float y, float z)
    {
        this->name = name;
        this->x = x;
        this->y = y;
        this->z = z;
    }
    virtual void draw() = 0;
};

#endif // AINPC_H
