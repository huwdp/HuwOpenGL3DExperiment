#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <GL/glut.h>

class TextureLoader
{
public:
    static GLuint loadTexture(std::string fileLocation);
};

#endif // TEXTURELOADER_H
