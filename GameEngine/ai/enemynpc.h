#ifndef ENEMYNPC_H
#define ENEMYNPC_H

#include <string>
#include <stack>

#include "ainpc.h"

class EnemyNPC : public AINPC
{
public:
    EnemyNPC(std::string name, float x, float y, float z);
    void draw();
};

#endif // ENEMYNPC_H
