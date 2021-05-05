#ifndef FACE3D_H
#define FACE3D_H


class Face3D
{
public:
    int vertex[3], uv[3], normal[3];
    bool quad = true;
    Face3D(bool quad);
};

#endif // FACE3D_H
