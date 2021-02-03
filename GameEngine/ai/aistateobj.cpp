#include "aistateobj.h"

AIStateObj::AIStateObj(int state, std::time_t timestamp, int seconds)
{
    this->state = state;
    this->timestamp = timestamp;
    this->seconds = seconds;
}
