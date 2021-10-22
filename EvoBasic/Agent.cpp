#include "Agent.h"

Agent::Agent() : actionType(0) 
{
    this->actionType = rand() % 3;
}

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

uint32_t Agent::GetActionType()
{
    return this->actionType;
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
    else if (this->actionType == 3)
    {
        type = this->ActionStrategyRandom();
    }

    return type;
}

EnumAgentActionType Agent::ActionStrategyRandom()
{
    uint32_t randNum = rand() % 3;

    return (EnumAgentActionType)randNum;
}