#include "Agent.h"
#include <algorithm>

// class Agent

Agent::Agent() : actionType_(0)
{
    this->actionType_ = rand() % 3;
}

uint32_t Agent::GetHealth()
{
    return this->health_;
}

void Agent::GetHurt(int damage)
{
    this->health_ = max(0, (int)(this->health_ - damage));
    return;
}

EnumAgentStatus Agent::GetStatus()
{
    if (this->health_ > 0)
    {
        return EnumAgentStatus::AGENT_STATUS_HEALTHY;
    }
    else
    {
        return EnumAgentStatus::AGENT_STATUS_DEAD;
    }
}

uint32_t Agent::GetActionType()
{
    return this->actionType_;
}

void Agent::ReadEnvBeforeAction()
{
    // Do something
}

void Agent::ReadEnvAfterAction()
{
    // Do something
}

EnumAgentActionType Agent::Action()
{
    EnumAgentActionType type = EnumAgentActionType::AGENT_ACTION_ROCK;

    if (this->actionType_ == 0)
    {
        type = EnumAgentActionType::AGENT_ACTION_ROCK;
    }
    else if (this->actionType_ == 1)
    {
        type = EnumAgentActionType::AGENT_ACTION_PAPER;
    }
    else if (this->actionType_ == 2)
    {
        type = EnumAgentActionType::AGENT_ACTION_SCISSOR;
    }
    else if (this->actionType_ == 3)
    {
        type = this->ActionStrategyRandom();
    }

    return type;
}

void Agent::HealthRevive()
{
    health_ = 10;
}

EnumAgentActionType Agent::ActionStrategyRandom()
{
    uint32_t randNum = rand() % 3;

    return (EnumAgentActionType)randNum;
}

// class CopyLastActionAgent

void CopyLastActionAgent::SetLastAction(EnumAgentActionType action)
{
    lastAction_ = action;
}

void CopyLastActionAgent::ReadEnvBeforeAction()
{
    // Do something
}

void CopyLastActionAgent::ReadEnvAfterAction(EnumAgentActionType action)
{
    SetLastAction(action);
}

EnumAgentActionType CopyLastActionAgent::Action()
{
    EnumAgentActionType type = EnumAgentActionType::AGENT_ACTION_ROCK;

    if (lastAction_ == EnumAgentActionType::AGENT_ACTION_ROCK)
    {
        type = EnumAgentActionType::AGENT_ACTION_PAPER;
    }
    else if (lastAction_ == EnumAgentActionType::AGENT_ACTION_PAPER)
    {
        type = EnumAgentActionType::AGENT_ACTION_SCISSOR;
    }
    else if (lastAction_ == EnumAgentActionType::AGENT_ACTION_SCISSOR)
    {
        type = EnumAgentActionType::AGENT_ACTION_ROCK;
    }

    return type;
}