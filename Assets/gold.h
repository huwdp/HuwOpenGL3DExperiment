#ifndef GOLD_H
#define GOLD_H

#include "drawable.h"

class Gold : public Drawable
{
public:
    Gold(float x, float y, float z);
    void draw();
};

#endif // GOLD_H
