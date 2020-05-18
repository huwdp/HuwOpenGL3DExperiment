#ifndef TEXTURE_H
#define TEXTURE_H

enum TextureLoadStatus { SUCCESS, INCORRECTFORMAT, FILEERROR };

#include <string>
#include <GL/glut.h>

class Texture
{
private:
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
public:
    Texture(std::string textureFileLocation);
    ~Texture();
    std::string textureFileLocation;
    unsigned int width, height;
    TextureLoadStatus load();
    int getSize();
    unsigned char *getData();
    unsigned char *data;
    GLuint texture;
};

#endif // TEXTURE_H
