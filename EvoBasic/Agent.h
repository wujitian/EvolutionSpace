#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef enum
{
    AGENT_ACTION_ROCK = 0,
    AGENT_ACTION_PAPER = 1,
    AGENT_ACTION_SCISSOR = 2,
    AGENT_ACTION_MAX
}EnumAgentActionType;

typedef enum
{
    AGENT_STATUS_HEALTHY = 0,
    AGENT_STATUS_DEAD = 1,
    AGENT_STATUS_MAX
}EnumAgentStatus;

class Agent
{
public:
    Agent();
    Agent(uint32_t actType) : actionType(actType) {};
    ~Agent() {};

    uint32_t GetHealth();
    void GetHurt();
    EnumAgentStatus GetStatus();
    uint32_t GetActionType();

    EnumAgentActionType Action();

private:
    uint32_t health = 10;
    uint32_t actionType = 0;

    // Different Actions
    EnumAgentActionType ActionStrategyRandom();
};