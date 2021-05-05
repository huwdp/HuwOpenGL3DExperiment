#ifndef WAVEFRONTOBJECT_H
#define WAVEFRONTOBJECT_H

#include "object.h"
#include <string>
#include <memory>
#include <vector>
#include "../coord2d.h"
#include "../coord3d.h"
#include "../face3d.h"

class WavefrontObject : public Object
{
private:
    float s;
    float r;
    float g;
    float b;
    void renderQuads();
    void renderTriangles();
public:
    bool quad = false;
    std::vector<std::shared_ptr<Face3D>> faces;
    std::vector<std::shared_ptr<Coord3D>> vertices;
    std::vector<std::shared_ptr<Coord2D>> uvs;
    std::vector<std::shared_ptr<Coord3D>> normals;
    WavefrontObject();
    void draw();
    std::string filePath;
};

#endif // WAVEFRONTOBJECT_H
