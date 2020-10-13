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
    if (collision)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    else
    {
        glColor3f(r, g, b);
    }

    float width = 1;
    float height = 1;


    // Left leg
    //glTranslatef(-1, 0, 0);

    /*glRotatef(90, x+(width/2), y, z);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, width, width, height, 32, 32);
    delete quadratic;
    glRotatef(-90, x-(width/2), y, z);
    //glTranslatef(+1, 0, 0);*/

    // Right leg
    //glTranslatef(1, 0, 0);

    //glutSolidCone(1,1,1,1);

    //glTranslatef(-1, 0, 0);

    // Body





    // Left arm

    // Right arm

    // Head



    //glutSolidCone(s);
    glTranslatef(-x, -y, -z);
}
