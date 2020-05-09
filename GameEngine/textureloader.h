#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <GL/glut.h>

class TextureLoader
{
public:
    TextureLoader();
    GLuint LoadTexture(std::string fileLocation);
};

#endif // TEXTURELOADER_H
