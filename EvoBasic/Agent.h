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

// ����CopyLastActionAgent�࣬���̳���Agent�࣬�ܹ���ס�����ϴε���Ϊ�����з���
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

    // ��д Action ������ʹ������� think �����Ľ����������
    virtual EnumAgentActionType Action()
    {
        // ���� think ������ȷ���ж�
        EnumAgentActionType action = think();

        // ���� think ����ȷ�����ж�
        return action;
    }

    void SetComponentLastAction(EnumAgentActionType action);
    void SetMyLastAction(EnumAgentActionType action);

    void ReadEnvBeforeAction();
    void ReadEnvAfterAction(EnumAgentActionType action);

private:
    // ����һЩ�߼�ȷ���ж��ĺ���
    EnumAgentActionType think();

    // ������������Ȩ�ؾ���
    vmath::mat3 inputWeights;
    // ����������ز�Ȩ�ؾ���
    vmath::mat3 hiddenWeights;

    EnumAgentActionType vecComponentLastAction_[3];
    EnumAgentActionType vecMyLastAction_[3];
};