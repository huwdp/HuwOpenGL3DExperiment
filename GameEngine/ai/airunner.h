#ifndef AIRUNNER_H
#define AIRUNNER_H

#include <vector>
#include <memory>
#include "ainpc.h"

class AIRunner
{
private:
public:
    AIRunner();
    static void runAI(std::vector<std::shared_ptr<AINPC>> npcs);
};

#endif // AIRUNNER_H
