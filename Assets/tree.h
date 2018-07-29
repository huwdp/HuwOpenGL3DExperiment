#ifndef TREE_H
#define TREE_H

#include "drawable.h"

class Tree : public Drawable
{
public:
    Tree(float x, float y, float z);
    void draw();
};

#endif // TREE_H
