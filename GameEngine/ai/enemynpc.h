#ifndef ENEMYNPC_H
#define ENEMYNPC_H

#include "ainpc.h"

#include <string>

class EnemyNPC : public AINPC
{
public:
    EnemyNPC(std::string name, float x, float y, float z);
    void draw();
};

#endif // ENEMYNPC_H
