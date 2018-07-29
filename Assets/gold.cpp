#include "gold.h"

Gold::Gold(float x, float y, float z) : Drawable(x, y, z)
{

}

void Gold::draw()
{
    glBegin(GL_POLYGON);

    glVertex3f( -0.5, -0.5, -0.5);       // P1
    glVertex3f( -0.5,  0.5, -0.5);       // P2
    glVertex3f(  0.5,  0.5, -0.5);       // P3
    glVertex3f(  0.5, -0.5, -0.5);       // P4

    glEnd();
}
