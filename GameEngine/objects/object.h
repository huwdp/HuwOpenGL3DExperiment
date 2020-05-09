#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
    float x;
    float y;
    float z;
    float width;
    float height;
    float length;
    bool collision;
    Object(float x, float y, float z, float width, float height, float length);
    virtual void draw() = 0;
};

#endif // OBJECT_H
