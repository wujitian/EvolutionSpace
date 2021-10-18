#include "Agent.h"

uint32_t Agent::GetHealth()
{
    return this->health;
}

void Agent::GetHurt()
{
    this->health--;
    return;
}

EnumAgentStatus Agent::GetStatus()
{
    if (this->health > 0)
    {
        return AGENT_STATUS_HEALTHY;
    }
    else
    {
        return AGENT_STATUS_DEAD;
    }
}

EnumAgentActionType Agent::Action()
{
    EnumAgentActionType type = AGENT_ACTION_ROCK;

    if (this->actionType == 0)
    {
        type = AGENT_ACTION_ROCK;
    }
    else if (this->actionType == 1)
    {
        type = AGENT_ACTION_PAPER;
    }
    else if (this->actionType == 2)
    {
        type = AGENT_ACTION_SCISSOR;
    }

    return type;
}

EnumAgentActionType ActionType0()
{
    return AGENT_ACTION_ROCK;
}