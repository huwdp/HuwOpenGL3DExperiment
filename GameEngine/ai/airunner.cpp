#include "airunner.h"

#include "enums.h"

AIRunner::AIRunner()
{

}

void AIRunner::runAI(std::vector<std::shared_ptr<AINPC>> npcs)
{
    for (auto it = npcs.begin(); it != npcs.end(); it++)
    {
        auto npc = (*it);
        auto currentState = npc->stateStack.top();
        std::time_t time = std::time(0);

        if (npc->health < 10 && currentState->state != 2) // FLEE
        {
            npc->stateStack.push(std::make_shared<AIStateObj>(2, time, 10));
        }

        if (currentState->state == 0) // IDLE10SEC
        {
            // Do nothing
            if (currentState->timestamp + currentState->seconds*1000 > time)
            {
                npc->stateStack.pop();
            }
        }
        else if (currentState->state == 1) // ATTACK
        {
            // Attack and follow player
            // TODO
        }
        else if (currentState->state == 2) // FLEE
        {
            // Find a place to hide and take cover
            // TODO
        }
        else if (currentState->state == 3) // PARTOL
        {
            // Randomly walk around slowly
            // TODO
        }

        // Heal
        if (npc->health < 100 && npc->lastTimeHealed < time-1000*10)
        {
            npc->health++;
            npc->lastTimeHealed = time;
        }
    }
}
