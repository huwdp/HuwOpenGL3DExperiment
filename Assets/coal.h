#ifndef COAL_H
#define COAL_H

#include "drawable.h"

class Coal : public Drawable
{
public:
    Coal(float x, float y, float z);
    void draw();
};

#endif // COAL_H
