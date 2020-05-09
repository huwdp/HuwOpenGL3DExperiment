#include "texture.h"

Texture::Texture(std::string textureFileLocation)
{
    this->textureFileLocation = textureFileLocation;
}

Texture::~Texture()
{
    delete data;
}

TextureLoadStatus Texture::load()
{
    FILE * file = fopen(textureFileLocation.c_str(),"rb");
    if (!file)
    {
        return FILEERROR;
    }
    if ( fread(header, 1, 54, file)!=54 )
    {
        return TextureLoadStatus::INCORRECTFORMAT;
    }
    if ( header[0]!='B' || header[1]!='M' )
    {
        return TextureLoadStatus::INCORRECTFORMAT;
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
    return SUCCESS;
}

int Texture::getSize()
{
    return imageSize;
}

unsigned char *Texture::getData()
{
    return data;
}
