#include "floor.h"

#include <GL/glut.h>

Floor::Floor(float x, float y, float z, float w, float l, float h, float r, float g, float b, std::shared_ptr<Texture> texture)
    : Object(x, y ,z, w, h, l)
{
    this->texture = texture;
    collidable = false;
}

void Floor::draw()
{
    glTranslatef(x, y, z);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->texture);

    float aniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 8, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texDat);

    glBindTexture(GL_TEXTURE_2D, texture->texture);

    glBegin(GL_POLYGON);
        glNormal3f(0.0f, 1.0f, 0.0f);	// top face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(width, length, height);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(width, length, -height);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, length, -height);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, length, height);
    glEnd();

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTranslatef(-x, -y, -z);
}
