#ifndef FRIENDLYNPC_H
#define FRIENDLYNPC_H

#include <string>
#include "ainpc.h"

class FriendlyNPC : public AINPC
{
public:
    FriendlyNPC(std::string name, float x, float y, float z);
    void draw();
};

#endif // FRIENDLYNPC_H
