#include "floor.h"

#include <GL/glut.h>
#include "../textureloader.h"

Floor::Floor(float x, float y, float z, float w, float h, float l, float r, float g, float b, std::string textureFileLocation)
    : Object(x, y ,z, w, h, l)
{
    this->textureFileLocation = textureFileLocation;
    collidable = false;
    load();
}

Floor::~Floor()
{
    //delete this->tex;
    delete this->texDat;
}

void Floor::load()
{
    if (textureFileLocation != "")
    {
        GLuint texture = TextureLoader::loadTexture(textureFileLocation);
        this->tex = texture;
        return;
    }
    else
    {
        for (int i = 0; i < 512; ++i)
        {
            texDat[i] = ((i + (i / 8)) % 2) * 128 + 127;
        }
    }
    glGenTextures(1, &tex);
}

void Floor::draw()
{

    glTranslatef(x, y, z);


    glEnable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, tex);


    float aniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

    /*
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);*/

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 8, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texDat);

    glBindTexture(GL_TEXTURE_2D, tex);

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
