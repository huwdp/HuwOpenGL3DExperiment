#include "friendlynpc.h"
#include <GL/glut.h>

FriendlyNPC::FriendlyNPC(std::string name, float x, float y, float z)
    : AINPC(name, x, y, z)
{

}

void FriendlyNPC::draw()
{
    glTranslatef(x, y, z);
    glColor3f(0.f, 1.f, 0.f);
    glutSolidCone(1, 2, 2, 2);
    glTranslatef(-x, -y, -z);
}
