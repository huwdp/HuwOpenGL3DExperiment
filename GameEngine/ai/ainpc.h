#ifndef AINPC_H
#define AINPC_H

#include <string>
#include <stack>
#include <memory>
#include <ctime>
#include "aistateobj.h"
#include "gridnode.h"

class AINPC
{
protected:

    std::stack<std::shared_ptr<AIStateObj>> stateStack;
public:
    std::time_t lastMoved;
    std::stack<std::shared_ptr<GridNode>> pathStack;

    int id;
    std::string name;
    int health = 100;
    float x;
    float y;
    float z;
    bool onAlert = false;

    int destGridX;
    int destGridY;

    std::time_t lastTimeHealed;
    AINPC(std::string name, float x, float y, float z)
    {
        this->name = name;
        this->x = x;
        this->y = y;
        this->z = z;
        this->lastMoved = std::time(0)*1000;
    }
    void pushToStack(std::shared_ptr<AIStateObj> state)
    {
        stateStack.push(state);
    }
    void popStack()
    {
        if (stateStack.size() > 1)
        {
            stateStack.pop();
        }
    }
    std::shared_ptr<AIStateObj> topStack()
    {
        return stateStack.top();
    }
    virtual void draw() = 0;
};

#endif // AINPC_H
