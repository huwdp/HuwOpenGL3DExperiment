#ifndef SKYBOX_H
#define SKYBOX_H

#include "object.h"
#include "../texture.h"
#include <string>
#include <GL/glut.h>
#include <memory>

class SkyBox : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    void load();
    std::shared_ptr<Texture> texture;
public:
    SkyBox(float x, float y, float z, float w, float l, float h, float r, float g, float b, std::shared_ptr<Texture> texture);
    SkyBox(float x, float y, float z, float w, float l, float h, float r, float g, float b, std::shared_ptr<Texture> texture, int id);
    void draw();
};
#endif // SKYBOX_H
