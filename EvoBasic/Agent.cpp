#include "Agent.h"
#include <algorithm>
#include <random>

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
    health_ = 20;
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

// class SmartAgent

SmartAgent::SmartAgent() : Agent()
{
    // ʹ�� std::random_device �� std::mt19937 ���������
    //std::random_device rd;    // �������
    //std::mt19937 gen(rd());   // α�����
    std::mt19937 gen(4);
    std::uniform_real_distribution<> dis(-0.1, 0.1);

    // ������������Ȩ�ؾ�������ز�Ȩ�ؾ���
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            inputWeights[i][j] = dis(gen);
            hiddenWeights[i][j] = dis(gen);
        }
    }

    // ������� vecComponentLastAction_ �� vecMyLastAction_ ����
    std::uniform_int_distribution<> disAction(0, 2);
    for (int i = 0; i < 3; ++i)
    {
        vecComponentLastAction_[i] = static_cast<EnumAgentActionType>(disAction(gen));
        vecMyLastAction_[i] = static_cast<EnumAgentActionType>(disAction(gen));
    }
}

void SmartAgent::SetComponentLastAction(EnumAgentActionType action)
{
    // �� vecComponentLastAction_ ����ĺ�����Ԫ�ؿ�����ǰ����Ԫ��
    vecComponentLastAction_[0] = vecComponentLastAction_[1];
    vecComponentLastAction_[1] = vecComponentLastAction_[2];

    // �� action �洢�� vecComponentLastAction_ ��������һ��Ԫ��
    vecComponentLastAction_[2] = action;
}

void SmartAgent::SetMyLastAction(EnumAgentActionType action)
{
    // �� vecMyLastAction_ ����ĺ�����Ԫ�ؿ�����ǰ����Ԫ��
    vecMyLastAction_[0] = vecMyLastAction_[1];
    vecMyLastAction_[1] = vecMyLastAction_[2];

    // �� action �洢�� vecMyLastAction_ ��������һ��Ԫ��
    vecMyLastAction_[2] = action;

}

void SmartAgent::ReadEnvBeforeAction()
{
    // Do something
}

void SmartAgent::ReadEnvAfterAction(EnumAgentActionType action)
{
    SetComponentLastAction(action);
}

EnumAgentActionType SmartAgent::think()
{
    // �� EnumAgentActionType ת��Ϊ float ���͵ĺ���
    auto convertToFloat = [](EnumAgentActionType actionType) -> float
    {
        return actionType == EnumAgentActionType::AGENT_ACTION_ROCK ? -1.0
            : actionType == EnumAgentActionType::AGENT_ACTION_PAPER ? 0.0
            : 1.0;
    };

    // ��ȡ����֮ǰ���Ķ���������ת��Ϊ mat3 ����ʽ
    vmath::mat3 inputMatrix;
    for (int i = 0; i < 3; i++)
    {
        // ������֮ǰ���Ķ����洢���������ݵĵ�һ��
        inputMatrix[i][0] = convertToFloat(vecComponentLastAction_[i]);
        // ������֮ǰ���Ķ����洢���������ݵĵڶ���
        inputMatrix[i][1] = convertToFloat(vecMyLastAction_[i]);
        inputMatrix[i][2] = 0;
    }

    // ʹ�þ�����˵ķ�ʽģ��������ļ������
    vmath::mat3 hidden = inputWeights * inputMatrix;
    vmath::mat3 output = hiddenWeights * hidden;

    // ��������ת��Ϊ EnumAgentActionType ����
    EnumAgentActionType action;
    if (output[0][0] > output[1][0] && output[0][0] > output[2][0])
    {
        action = EnumAgentActionType::AGENT_ACTION_ROCK;
    }
    else if (output[1][0] > output[0][0] && output[1][0])
    {
        action = EnumAgentActionType::AGENT_ACTION_PAPER;
    }
    else
    {
        action = EnumAgentActionType::AGENT_ACTION_SCISSOR;
    }

    // ���õ�ǰ�����ǵ�action
    SetMyLastAction(action);

    return action;
}