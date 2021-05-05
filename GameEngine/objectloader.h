#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <memory>
#include "objects/wavefrontobject.h"

class ObjectLoader
{
public:
    static std::shared_ptr<WavefrontObject> loadObject(std::string filePath);
};

#endif // OBJECTLOADER_H
