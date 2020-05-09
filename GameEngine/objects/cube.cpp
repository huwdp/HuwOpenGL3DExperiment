#include "cube.h"
#include <GL/glut.h>

Cube::Cube(float x, float y, float z, float s, float r, float g, float b)
    : Object(x, y, z, s, s, s)
{
    this->s = s;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Cube::draw()
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
    glutSolidCube(s);
    glTranslatef(-x, -y, -z);
}
