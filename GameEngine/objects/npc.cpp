#include "npc.h"

NPC::NPC(float x, float y, float z, float s, float r, float g, float b)
    : Object(x, y, z, s, s, s)
{
    this->s = s;
    this->r = r;
    this->g = g;
    this->b = b;
}

void NPC::draw()
{
    glTranslatef(x, y, z);

    float width = 1;
    float height = 1;

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(s);

    //glutSolidCone(s);
    glTranslatef(-x, -y, -z);
}
