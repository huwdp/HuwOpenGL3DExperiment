#include "texturedcube.h"

#include <GL/glut.h>

TexturedCube::TexturedCube(float x, float y, float z, float w, float h, float l, float r, float g, float b, std::string textureFileLocation)
    : Object(x, y ,z, w, h, l)
{
    this->textureFileLocation = textureFileLocation;
    load();
}

void TexturedCube::load()
{
}

void TexturedCube::draw()
{
    unsigned char texDat[512];
    for (int i = 0; i < 512; ++i)
        texDat[i] = ((i + (i / 8)) % 2) * 128 + 127;

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTranslatef(x, y, z);


    //width=width/2.0; height = height/2.0; length = length/2.0;

    glEnable(GL_TEXTURE_2D);


    float aniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 8, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texDat);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_POLYGON);
        glNormal3f(0.0f, 1.0f, 0.0f);	// top face
        glTexCoord2f(0.0f, 0.0f); glVertex3f(width, length, height);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(width, length, -height);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, length, -height);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, length, height);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0.0f, 0.0f, 1.0f);	// front face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(width, length, height);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-width, length, height);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(-width, -length, height);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(width, -length, height);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(1.0f, 0.0f, 0.0f);	// right face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(width, length, height);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(width, -length, height);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(width, -length, -height);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(width, length, -height);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(-width, length, height);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-width, length, -height);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(-width, -length, -height);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(-width, -length, height);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0.0f, -1.0f, 0.0f);	// bottom face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(-width, -length, height);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-width, -length, -height);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(width, -length, -height);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(width, -length, height);
    glEnd();
    glBegin(GL_POLYGON);
        glNormal3f(0.0f, 0.0f, -1.0f);	// back face
        glTexCoord2f(0.0f, 0.0f);glVertex3f(width, -length, -height);
        glTexCoord2f(1.0f, 0.0f);glVertex3f(-width, -length, -height);
        glTexCoord2f(1.0f, 1.0f);glVertex3f(-width, length, -height);
        glTexCoord2f(0.0f, 1.0f);glVertex3f(width, length, -height);
    glEnd();

    /*glBegin(GL_QUADS);

    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, -1.0f,  1.0f);// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad

    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad

    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad

    // Bottom Face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad

    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad

    glEnd();					// Done Drawing The Cube*/



    // Picture
    //glTexCoord3f(0, 0, 1); glVertex3f(1, 1, 1);
    //glTexCoord3f(0, 1, 1); glVertex3f(1, 5, 1);
    //glTexCoord3f(1, 1, 1); glVertex3f(5, 5, 1);
    //glTexCoord3f(1, 0, 1); glVertex3f(5, 1, 1);
    //glTexCoord2i(0, 0); glVertex2i(1, 1);
    //glTexCoord2i(0, 1); glVertex2i(1, 5);
    //glTexCoord2i(1, 1); glVertex2i(5, 5);
    //glTexCoord2i(1, 0); glVertex2i(5, 1);


    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTranslatef(-x, -y, -z);
}
