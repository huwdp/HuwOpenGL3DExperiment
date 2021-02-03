#ifndef AISTATEOBJ_H
#define AISTATEOBJ_H

#include <iostream>
#include <ctime>

#include "enums.h"

class AIStateObj
{
public:
    AIStateObj(int state, std::time_t timestamp, int seconds);
    int state;
    std::time_t timestamp;
    int seconds;
};

#endif // AISTATEOBJ_H
