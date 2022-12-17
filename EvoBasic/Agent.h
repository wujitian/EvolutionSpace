#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "vmath.h"
#include <vector>

using namespace std;

typedef enum class EnumAgentActionType
{
    AGENT_ACTION_ROCK = 0,
    AGENT_ACTION_PAPER = 1,
    AGENT_ACTION_SCISSOR = 2,
    AGENT_ACTION_MAX
}EnumAgentActionType;

typedef enum class EnumAgentStatus
{
    AGENT_STATUS_HEALTHY = 0,
    AGENT_STATUS_DEAD = 1,
    AGENT_STATUS_MAX
}EnumAgentStatus;

class Agent
{
public:
    Agent();
    Agent(uint32_t actType) : actionType_(actType) {};
    ~Agent() {};

    uint32_t GetHealth();
    void GetHurt(int damage);
    EnumAgentStatus GetStatus();
    uint32_t GetActionType();

    virtual void ReadEnvBeforeAction();
    virtual void ReadEnvAfterAction();
    virtual EnumAgentActionType Action();

    void HealthRevive();

private:
    uint32_t health_ = 20;
    uint32_t actionType_ = 0;

    // Different Actions
    EnumAgentActionType ActionStrategyRandom();
};

// 定义CopyLastActionAgent类，它继承自Agent类，能够记住对手上次的行为，进行反制
class CopyLastActionAgent : public Agent
{
public:
    CopyLastActionAgent() { Agent(); };
    CopyLastActionAgent(uint32_t actType) : Agent(actType), lastAction_(EnumAgentActionType::AGENT_ACTION_ROCK) {};
    ~CopyLastActionAgent() {};

    void SetLastAction(EnumAgentActionType action);

    void ReadEnvBeforeAction();
    void ReadEnvAfterAction(EnumAgentActionType action);
    EnumAgentActionType Action();

private:
    EnumAgentActionType lastAction_;
};

class SmartAgent : public Agent
{
public:
    SmartAgent();
    SmartAgent(uint32_t actType) : Agent(actType) {}
    ~SmartAgent() {}

    // 重写 Action 函数，使代理根据 think 函数的结果做出决策
    virtual EnumAgentActionType Action()
    {
        // 调用 think 函数来确定行动
        EnumAgentActionType action = think();

        // 返回 think 函数确定的行动
        return action;
    }

    void SetComponentLastAction(EnumAgentActionType action);
    void SetMyLastAction(EnumAgentActionType action);

    void ReadEnvBeforeAction();
    void ReadEnvAfterAction(EnumAgentActionType action);

private:
    // 根据一些逻辑确定行动的函数
    EnumAgentActionType think();

    // 神经网络的输入层权重矩阵
    vmath::mat3 inputWeights;
    // 神经网络的隐藏层权重矩阵
    vmath::mat3 hiddenWeights;

    EnumAgentActionType vecComponentLastAction_[3];
    EnumAgentActionType vecMyLastAction_[3];
};