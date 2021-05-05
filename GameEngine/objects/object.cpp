#include "object.h"

Object::Object()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->width = 0;
    this->height = 0;
    this->length = 0;
}

Object::Object(float x, float y, float z, float width, float height, float length)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = width;
    this->height = height;
    this->length = length;
}

Object::Object(float x, float y, float z, float width, float height, float length, int id)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = width;
    this->height = height;
    this->length = length;
    this->id = id;
}
