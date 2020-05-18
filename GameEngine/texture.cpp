#include "texture.h"

Texture::Texture(std::string textureFileLocation)
{
    this->textureFileLocation = textureFileLocation;
    load();
}

Texture::~Texture()
{
    delete data;
}

TextureLoadStatus Texture::load()
{
    FILE * file = fopen(textureFileLocation.c_str(),"rb");

    TextureLoadStatus errorCode = SUCCESS;

    if (!file)
    {
        errorCode = FILEERROR;
    }

    if ( fread(header, 1, 54, file)!=54 )
    {
        errorCode = INCORRECTFORMAT;
    }
    if ( header[0]!='B' || header[1]!='M' )
    {
        errorCode = INCORRECTFORMAT;
    }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    if (imageSize==0)    imageSize=width*height*3;
    if (dataPos==0)      dataPos=54;
    data = new unsigned char [imageSize];
    fread(data,1,imageSize,file);
    fclose(file);

    for (int i = 0; i < width * height ; ++i)
    {
        int index = i*3;
        unsigned char B,R;
        B = data[index];
        R = data[index+2];

        data[index] = R;
        data[index+2] = B;
    }

    // Generate checkerboard if failure occurred
    if (errorCode != SUCCESS)
    {
        for (int i = 0; i < 512; ++i)
        {
            data[i] = ((i + (i / 8)) % 2) * 128 + 127;
        }
    }

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
    return errorCode;
}

int Texture::getSize()
{
    return imageSize;
}

unsigned char *Texture::getData()
{
    return data;
}
