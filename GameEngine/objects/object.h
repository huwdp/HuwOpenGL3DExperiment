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
    bool collision = false;
    bool collidable = true;
    int id = 0;
    Object();
    Object(float x, float y, float z, float width, float height, float length);
    Object(float x, float y, float z, float width, float height, float length, int id);
    virtual void draw() = 0;
};

#endif // OBJECT_H
