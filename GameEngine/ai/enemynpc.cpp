#include "enemynpc.h"
#include <GL/glut.h>

EnemyNPC::EnemyNPC(std::string name, float x, float y, float z)
    : AINPC(name, x, y, z)
{

}

void EnemyNPC::draw()
{
    glTranslatef(x, y, z);
    if (onAlert)
    {
        glColor3f(0.0f, .0f, .0f);
    }
    else
    {
        glColor3f(0.0f, 1.0f, .0f);
    }
    glutSolidCube(2);
    glTranslatef(-x, -y, -z);
}
