#include "enemynpc.h"
#include <GL/glut.h>

EnemyNPC::EnemyNPC(std::string name, float x, float y, float z)
    : AINPC(name, x, y, z)
{
    // Set default state to idle
    stateStack.push(std::make_shared<AIStateObj>(0, std::time(0)*1000, 10));
}

void EnemyNPC::draw()
{
    glPushMatrix();
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
    glPopMatrix();
}
