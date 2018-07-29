#include "tree.h"

Tree::Tree(float x, float y, float z) : Drawable(x, y, z)
{

}

void Tree::draw()
{
    glPointSize(10.0f);
    glTranslatef((float)x, (float)y, (float)z);

    glColor3b(0.0, 255.0, 0.0);

    glBegin(GL_QUADS);

        glVertex3f(0, 0, 0);
        glVertex3f(100, 0, 0);
        glVertex3f(100, 100, 0);
        glVertex3f(0, 100, 0);
    glEnd();

    glPointSize(0.0f);
}
