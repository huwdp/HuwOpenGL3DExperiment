#include "sphere.h"

Sphere::Sphere(float x, float y, float z, float s, float r, float g, float b)
    : Object(x, y, z, s, s, s)
{
    this->s = s;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Sphere::draw()
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
    glutSolidCone(s, 2, 2, 2);
    glTranslatef(-x, -y, -z);
}
