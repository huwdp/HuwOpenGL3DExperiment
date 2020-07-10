#include "texturedcube.h"

#include <GL/glut.h>

TexturedCube::TexturedCube(float x, float y, float z, float w, float l, float h, float r, float g, float b, std::shared_ptr<Texture> texture)
    : Object(x, y ,z, w, h, l)
{
    this->texture = texture;
}

TexturedCube::TexturedCube(float x, float y, float z, float w, float l, float h, float r, float g, float b, std::shared_ptr<Texture> texture, int id)
    : Object(x, y ,z, w, h, l, id)
{
    this->texture = texture;
}

void TexturedCube::draw()
{
    glTranslatef(x, y, z);


    glEnable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, texture->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    float aniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 8, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texDat);

    //glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_POLYGON);
        glNormal3f(0.0f, 1.0f, 0.0f);	// top face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(width, height, length);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(width, height, -length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height, -length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, height, length);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0.0f, 0.0f, 1.0f);	// front face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(width, height, length);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-width, height, length);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(-width, -height, length);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(width, -height, length);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(1.0f, 0.0f, 0.0f);	// right face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(width, height, length);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(width, -height, length);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(width, -height, -length);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(width, height, -length);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(-width, height, length);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-width, height, -length);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(-width, -height, -length);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(-width, -height, length);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0.0f, -1.0f, 0.0f);	// bottom face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(-width, -height, length);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-width, -height, -length);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(width, -height, -length);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(width, -height, length);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0.0f, 0.0f, -1.0f);	// back face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(width, -height, -length);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-width, -height, -length);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(-width, height, -length);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(width, height, -length);
    glEnd();


    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTranslatef(-x, -y, -z);
}
